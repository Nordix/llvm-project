set(LLVM_LINK_COMPONENTS
  Support
  )

add_llvm_unittest(ADTTests
  AnyTest.cpp
  APFixedPointTest.cpp
  APFloatTest.cpp
  APIntTest.cpp
  APSIntTest.cpp
  ArrayRefTest.cpp
  BitFieldsTest.cpp
  BitmaskEnumTest.cpp
  BitTest.cpp
  BitVectorTest.cpp
  BreadthFirstIteratorTest.cpp
  BumpPtrListTest.cpp
  CoalescingBitVectorTest.cpp
  CombinationGeneratorTest.cpp
  ConcurrentHashtableTest.cpp
  CountCopyAndMove.cpp
  DAGDeltaAlgorithmTest.cpp
  DeltaAlgorithmTest.cpp
  DenseMapTest.cpp
  DenseSetTest.cpp
  DepthFirstIteratorTest.cpp
  DirectedGraphTest.cpp
  DynamicAPIntTest.cpp
  EditDistanceTest.cpp
  EnumeratedArrayTest.cpp
  EquivalenceClassesTest.cpp
  FallibleIteratorTest.cpp
  FloatingPointMode.cpp
  FoldingSet.cpp
  FunctionExtrasTest.cpp
  FunctionRefTest.cpp
  HashingTest.cpp
  IListBaseTest.cpp
  IListIteratorTest.cpp
  IListIteratorBitsTest.cpp
  IListNodeBaseTest.cpp
  IListNodeTest.cpp
  IListSentinelTest.cpp
  IListTest.cpp
  ImmutableListTest.cpp
  ImmutableMapTest.cpp
  ImmutableSetTest.cpp
  IntEqClassesTest.cpp
  Interleave.cpp
  IntervalMapTest.cpp
  IntervalTreeTest.cpp
  IntrusiveRefCntPtrTest.cpp
  IteratorTest.cpp
  LazyAtomicPointerTest.cpp
  MappedIteratorTest.cpp
  MapVectorTest.cpp
  PackedVectorTest.cpp
  PagedVectorTest.cpp
  PointerEmbeddedIntTest.cpp
  PointerIntPairTest.cpp
  PointerSumTypeTest.cpp
  PointerUnionTest.cpp
  PostOrderIteratorTest.cpp
  PriorityWorklistTest.cpp
  RangeAdapterTest.cpp
  RewriteBufferTest.cpp
  SCCIteratorTest.cpp
  STLExtrasTest.cpp
  STLForwardCompatTest.cpp
  ScopedHashTableTest.cpp
  ScopeExitTest.cpp
  SequenceTest.cpp
  SetOperationsTest.cpp
  SetVectorTest.cpp
  SimpleIListTest.cpp
  SmallPtrSetTest.cpp
  SmallSetTest.cpp
  SmallStringTest.cpp
  SmallVectorExtrasTest.cpp
  SmallVectorTest.cpp
  SparseBitVectorTest.cpp
  SparseMultiSetTest.cpp
  SparseSetTest.cpp
  StatisticTest.cpp
  StringExtrasTest.cpp
  StringMapTest.cpp
  StringRefTest.cpp
  StringSetTest.cpp
  StringSwitchTest.cpp
  StringTableTest.cpp
  TinyPtrVectorTest.cpp
  TrieRawHashMapTest.cpp
  TwineTest.cpp
  TypeSwitchTest.cpp
  TypeTraitsTest.cpp
  )

target_link_libraries(ADTTests PRIVATE LLVMTestingSupport)

add_dependencies(ADTTests intrinsics_gen)
