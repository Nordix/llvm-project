; Test that strip-path-components strips path components from module name
; The module ID is set by opt to the input filename, so we test with the actual path
; RUN: opt %s -passes='asan<strip-path-components=-1>' -S | FileCheck %s --check-prefix=LAST-ONLY

target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@global = global i32 0, align 4

; LAST-ONLY: @___asan_gen_module = private constant [{{[0-9]+}} x i8] c"asan-strip-path-components.ll\00"

define void @f() sanitize_address {
  ret void
}
