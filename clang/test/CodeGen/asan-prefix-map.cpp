// RUN: mkdir -p %t.dir
// RUN: cp %s %t.dir/test.c
// RUN: %clang_cc1 -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address %t.dir/test.c -o - | FileCheck -check-prefix=REGULAR %s
// RUN: %clang_cc1 -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address -fsanitize-prefix-map=%t.dir/= %t.dir/test.c -o - | FileCheck -check-prefix=REMAPPED %s

// REGULAR: @___asan_gen_module = private constant [{{.*}} x i8] c"{{.+}}test.c\00"
// REMAPPED: @___asan_gen_module = private constant [{{.*}} x i8] c"test.c\00"

int global;

void f() {
  global = 1;
}
