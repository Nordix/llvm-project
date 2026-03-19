// RUN: %clang -### -fsanitize=address -fsanitize-compilation-dir=/foo %s 2>&1 | FileCheck %s --check-prefix=SANITIZE
// RUN: %clang -### -fsanitize=undefined -fsanitize-compilation-dir=/foo %s 2>&1 | FileCheck %s --check-prefix=SANITIZE
// RUN: %clang -### -fsanitize=address -ffile-compilation-dir=/foo %s 2>&1 | FileCheck %s --check-prefix=FILE
// RUN: %clang -### -fsanitize=undefined -ffile-compilation-dir=/foo %s 2>&1 | FileCheck %s --check-prefix=FILE
// SANITIZE: "-fsanitize-compilation-dir=/foo"
// FILE: "-fsanitize-compilation-dir=/foo"
