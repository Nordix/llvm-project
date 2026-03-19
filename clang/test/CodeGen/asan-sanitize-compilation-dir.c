// Verify that -fsanitize-compilation-dir strips the directory prefix from
// the ASan module name embedded in instrumented code.

// RUN: mkdir -p %t.dir && cd %t.dir
// RUN: cp %s rel.c
// RUN: %clang_cc1 -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address %t.dir/rel.c -o - | FileCheck -check-prefix=CHECK-ABSOLUTE %s
// RUN: %clang_cc1 -triple=x86_64-linux-gnu -emit-llvm -fsanitize=address -fsanitize-compilation-dir=%t.dir %t.dir/rel.c -o - | FileCheck -check-prefix=CHECK-STRIPPED %s

// CHECK-ABSOLUTE: @___asan_gen_module = private constant [{{.*}} x i8] c"{{.+}}rel.c\00"
// CHECK-STRIPPED: @___asan_gen_module = private constant [{{.*}} x i8] c"rel.c\00"
int x;
