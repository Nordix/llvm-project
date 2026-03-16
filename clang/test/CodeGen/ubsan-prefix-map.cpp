// RUN: %clang %s -target x86_64-linux-gnu -emit-llvm -S -fsanitize=undefined -o - | FileCheck %s -check-prefix=REGULAR
// RUN: %clang %s -target x86_64-linux-gnu -emit-llvm -S -fsanitize=undefined -fsanitize-prefix-map=%S/= -o - | FileCheck %s -check-prefix=REMAPPED

// REGULAR: @{{.*}} = {{.*}} c"{{.*test(.|\\\\)CodeGen(.|\\\\)ubsan-prefix-map\.cpp}}\00"
// REMAPPED: @{{.*}} = {{.*}} c"ubsan-prefix-map.cpp\00"

int f(int x, int y) {
  return x / y;
}
