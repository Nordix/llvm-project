// RUN: %clang %s -### -o %t.o -fsanitize=address -fsanitize-prefix-map=/old=/new 2>&1 | FileCheck %s
// CHECK: "-fsanitize-prefix-map=/old=/new"
