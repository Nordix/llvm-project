// Verify that -fsanitize-compilation-dir strips the directory prefix from
// filenames embedded in UBSan check metadata.
//
// We use -fsanitize=unreachable (one of the checks under -fsanitize=undefined)
// rather than -fsanitize=undefined because the latter is a driver-level umbrella
// flag not accepted by CC1. Any individual sanitizer check exercises the same
// EmitCheckSourceLocation path.

// RUN: mkdir -p %t.dir && cd %t.dir
// RUN: cp %s test.c
// RUN: %clang_cc1 -triple=x86_64-linux-gnu -emit-llvm -fsanitize=unreachable %t.dir/test.c -o - | FileCheck -check-prefix=CHECK-DEFAULT %s
// RUN: %clang_cc1 -triple=x86_64-linux-gnu -emit-llvm -fsanitize=unreachable -fsanitize-compilation-dir=%t.dir/ %t.dir/test.c -o - | FileCheck -check-prefix=CHECK-STRIPPED %s

// CHECK-DEFAULT: @{{.*}} = private unnamed_addr constant [{{.*}} x i8] c"{{.+}}test.c\00"
// CHECK-STRIPPED: @{{.*}} = private unnamed_addr constant [{{.*}} x i8] c"test.c\00"
void f(void) {
  __builtin_unreachable();
}
