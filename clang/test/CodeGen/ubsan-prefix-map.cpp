// We use -fsanitize=signed-integer-overflow (included in -fsanitize=undefined)
// rather than -fsanitize=undefined because the latter is a driver-level umbrella
// flag not accepted by cc1.

// RUN: mkdir -p %t.dir
// RUN: cp %s %t.dir/test.cpp
// RUN: %clang_cc1 -triple=x86_64-linux-gnu -emit-llvm -fsanitize=signed-integer-overflow %t.dir/test.cpp -o - | FileCheck -check-prefix=REGULAR %s
// RUN: %clang_cc1 -triple=x86_64-linux-gnu -emit-llvm -fsanitize=signed-integer-overflow -fsanitize-prefix-map=%t.dir/= %t.dir/test.cpp -o - | FileCheck -check-prefix=REMAPPED %s

// REGULAR: @{{.*}} = private unnamed_addr constant [{{.*}} x i8] c"{{.+}}test.cpp\00"
// REMAPPED: @{{.*}} = private unnamed_addr constant [{{.*}} x i8] c"test.cpp\00"

int f(int x, int y) {
  return x / y;
}
