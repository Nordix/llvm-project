// RUN: %clang %s -### -o %t.o -fsanitize=address -fsanitize-prefix-map=/old=/new 2>&1 | FileCheck %s --check-prefix=SANITIZE
// RUN: %clang %s -### -o %t.o -fsanitize=undefined -fsanitize-prefix-map=/old=/new 2>&1 | FileCheck %s --check-prefix=SANITIZE
// SANITIZE: "-fsanitize-prefix-map=/old=/new"
