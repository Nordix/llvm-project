// RUN: %clang %s -### -o %t.o -fsanitize=address -fsanitize-address-strip-path-components=42 2>&1 | FileCheck %s
// CHECK: "-fsanitize-address-strip-path-components=42"
