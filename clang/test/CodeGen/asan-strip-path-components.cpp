// RUN: %clang_cc1 %s -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address -o - | FileCheck %s -check-prefix=REGULAR
// RUN: %clang_cc1 %s -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address -o - -fsanitize-address-strip-path-components=0 | FileCheck %s -check-prefix=REGULAR
// RUN: %clang_cc1 %s -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address -o - -fsanitize-address-strip-path-components=2 | FileCheck %s -check-prefix=REMOVE-FIRST-TWO

// Try to strip too much:
// RUN: %clang_cc1 %s -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address -o - -fsanitize-address-strip-path-components=-99999 | FileCheck %s -check-prefix=REGULAR
// RUN: %clang_cc1 %s -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address -o - -fsanitize-address-strip-path-components=99999 | FileCheck %s -check-prefix=LAST-ONLY

// Check stripping from the file name
// RUN: %clang_cc1 %s -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address -o - -fsanitize-address-strip-path-components=-2 | FileCheck %s -check-prefix=LAST-TWO
// RUN: %clang_cc1 %s -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address -o - -fsanitize-address-strip-path-components=-1 | FileCheck %s -check-prefix=LAST-ONLY

// REGULAR: @___asan_gen_module = private constant [{{[0-9]+}} x i8] c"{{.*test(.|\\\\)CodeGen(.|\\\\)asan-strip-path-components\.cpp}}\00"

// REMOVE-FIRST-TWO: @___asan_gen_module = private constant [{{[0-9]+}} x i8] c"{{.*asan-strip-path-components\.cpp}}\00"

// LAST-TWO: @___asan_gen_module = private constant [{{[0-9]+}} x i8] c"CodeGen{{/|\\\\}}asan-strip-path-components.cpp\00"
// LAST-ONLY: @___asan_gen_module = private constant [{{[0-9]+}} x i8] c"asan-strip-path-components.cpp\00"

int global;

void f() {
  global = 1;
}
