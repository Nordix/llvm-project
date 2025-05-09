# RUN: %PYTHON %s | FileCheck %s

import gc
from tempfile import NamedTemporaryFile
from mlir.ir import *


def run(f):
    print("\nTEST:", f.__name__)
    f()
    gc.collect()
    assert Context._get_live_count() == 0
    return f


# Verify successful parse.
# CHECK-LABEL: TEST: testParseSuccess
# CHECK: module @successfulParse
@run
def testParseSuccess():
    ctx = Context()
    module = Module.parse(r"""module @successfulParse {}""", ctx)
    assert module.context is ctx
    print("CLEAR CONTEXT")
    ctx = None  # Ensure that module captures the context.
    gc.collect()
    module.dump()  # Just outputs to stderr. Verifies that it functions.
    print(str(module))


# Verify successful parse from file.
# CHECK-LABEL: TEST: testParseFromFileSuccess
# CHECK: module @successfulParse
@run
def testParseFromFileSuccess():
    ctx = Context()
    with NamedTemporaryFile(mode="w") as tmp_file:
        tmp_file.write(r"""module @successfulParse {}""")
        tmp_file.flush()
        module = Module.parseFile(tmp_file.name, ctx)
        assert module.context is ctx
        print("CLEAR CONTEXT")
        ctx = None  # Ensure that module captures the context.
        gc.collect()
        module.operation.verify()
        print(str(module))


# Verify parse error.
# CHECK-LABEL: TEST: testParseError
# CHECK: testParseError: <
# CHECK:   Unable to parse module assembly:
# CHECK:   error: "-":1:1: expected operation name in quotes
# CHECK: >
@run
def testParseError():
    ctx = Context()
    try:
        module = Module.parse(r"""}SYNTAX ERROR{""", ctx)
    except MLIRError as e:
        print(f"testParseError: <{e}>")
    else:
        print("Exception not produced")


# Verify successful parse.
# CHECK-LABEL: TEST: testCreateEmpty
# CHECK: module {
@run
def testCreateEmpty():
    ctx = Context()
    loc = Location.unknown(ctx)
    module = Module.create(loc)
    print("CLEAR CONTEXT")
    ctx = None  # Ensure that module captures the context.
    gc.collect()
    print(str(module))


# Verify round-trip of ASM that contains unicode.
# Note that this does not test that the print path converts unicode properly
# because MLIR asm always normalizes it to the hex encoding.
# CHECK-LABEL: TEST: testRoundtripUnicode
# CHECK: func private @roundtripUnicode()
# CHECK: foo = "\F0\9F\98\8A"
@run
def testRoundtripUnicode():
    ctx = Context()
    module = Module.parse(
        r"""
    func.func private @roundtripUnicode() attributes { foo = "😊" }
  """,
        ctx,
    )
    print(str(module))


# Verify round-trip of ASM that contains unicode.
# Note that this does not test that the print path converts unicode properly
# because MLIR asm always normalizes it to the hex encoding.
# CHECK-LABEL: TEST: testRoundtripBinary
# CHECK: func private @roundtripUnicode()
# CHECK: foo = "\F0\9F\98\8A"
@run
def testRoundtripBinary():
    with Context():
        module = Module.parse(
            r"""
      func.func private @roundtripUnicode() attributes { foo = "😊" }
    """
        )
        binary_asm = module.operation.get_asm(binary=True)
        assert isinstance(binary_asm, bytes)
        module = Module.parse(binary_asm)
        print(module)


# Tests that module.operation works and correctly interns instances.
# CHECK-LABEL: TEST: testModuleOperation
@run
def testModuleOperation():
    ctx = Context()
    module = Module.parse(r"""module @successfulParse {}""", ctx)
    assert ctx._get_live_module_count() == 1
    op1 = module.operation
    assert ctx._get_live_operation_count() == 1
    live_ops = ctx._get_live_operation_objects()
    assert len(live_ops) == 1
    assert live_ops[0] is op1
    live_ops = None
    # CHECK: module @successfulParse
    print(op1)

    # Ensure that operations are the same on multiple calls.
    op2 = module.operation
    assert ctx._get_live_operation_count() == 1
    assert op1 is op2

    # Test live operation clearing.
    op1 = module.operation
    assert ctx._get_live_operation_count() == 1
    num_invalidated = ctx._clear_live_operations()
    assert num_invalidated == 1
    assert ctx._get_live_operation_count() == 0
    op1 = None
    gc.collect()
    op1 = module.operation

    # Ensure that if module is de-referenced, the operations are still valid.
    module = None
    gc.collect()
    print(op1)

    # Collect and verify lifetime.
    op1 = None
    op2 = None
    gc.collect()
    print("LIVE OPERATIONS:", ctx._get_live_operation_count())
    assert ctx._get_live_operation_count() == 0
    assert ctx._get_live_module_count() == 0


# CHECK-LABEL: TEST: testModuleCapsule
@run
def testModuleCapsule():
    ctx = Context()
    module = Module.parse(r"""module @successfulParse {}""", ctx)
    assert ctx._get_live_module_count() == 1
    # CHECK: "mlir.ir.Module._CAPIPtr"
    module_capsule = module._CAPIPtr
    print(module_capsule)
    module_dup = Module._CAPICreate(module_capsule)
    assert module is module_dup
    assert module_dup.context is ctx
    # Gc and verify destructed.
    module = None
    module_capsule = None
    module_dup = None
    gc.collect()
    assert ctx._get_live_module_count() == 0
