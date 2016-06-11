#include "Utils.hpp"
#include "UnitTest.hpp"

// TEST_CASE(TypeDisplayer)
// {
//     auto x = {3};
//     CYTL::TypeDisplayer<decltype(x)> xType;
// }

// TEST_CASE(NonCopyable)
// {
//     struct T: public CYTL::NonCopyable {};

//     T a;
//     T b(a); // compiling error

//     T c;
//     c = a; // compiling error
// }

TEST_CASE(arraySize)
{
    int keyVals[] = {1, 2, 3, 4, 5, 6};
    static_assert(CYTL::arraySize(keyVals) == 6, "arraySize error");
}

TEST_CASE(IfThenElse)
{
    struct T; struct F;

    CYTL::StaticTypeCheckEQ<CYTL::IfThenElse<true, T, F>, T>();
    CYTL::StaticTypeCheckEQ<CYTL::IfThenElse<false, T, F>, F>();
}

TEST_CASE(EnableIf)
{
    struct T;
    CYTL::StaticTypeCheckEQ<CYTL::EnableIf<true, T>, T>();
}

TEST_CASE(RemoveQualifiers)
{
    CYTL::StaticTypeCheckEQ<CYTL::RemoveConst<const volatile int>, volatile int>();
    CYTL::StaticTypeCheckEQ<CYTL::RemoveConst<int>, int>();

    CYTL::StaticTypeCheckEQ<CYTL::RemoveVolatile<const volatile int>, const int>();
    CYTL::StaticTypeCheckEQ<CYTL::RemoveVolatile<int&>, int&>();

    CYTL::StaticTypeCheckEQ<CYTL::RemoveConstVolatile<const volatile int>, int>();
    CYTL::StaticTypeCheckEQ<CYTL::RemoveConstVolatile<int>, int>();

    CYTL::StaticTypeCheckEQ<CYTL::RemoveReference<int&>, int>();
    CYTL::StaticTypeCheckEQ<CYTL::RemoveReference<int&&>, int>();
    CYTL::StaticTypeCheckEQ<CYTL::RemoveReference<int>, int>();
}

TEST_CASE(UnderlyingType)
{
    enum class E :int{ A=1, B=2, C=3 };
    CYTL::StaticTypeCheckEQ<CYTL::UnderlyingType<E>, int>();

    E e(E::B);
    EXPECT_EQ(CYTL::toUnderlyingType(e), 2);

    enum E1{ A=1, B=2, C=3 };
    CYTL::StaticTypeCheckEQ<CYTL::UnderlyingType<E1>, int>();

    E1 e1(C);
    EXPECT_EQ(CYTL::toUnderlyingType(e1), 3);
}

TEST_CASE(ConstIterator)
{
    int arr[] = {1, 2, 3, 4};

    EXPECT_EQ(CYTL::cbegin(arr), arr);
    EXPECT_EQ(CYTL::cend(arr), arr + CYTL::arraySize(arr));

    CYTL::StaticTypeCheckEQ<decltype( CYTL::cbegin(arr) ), const int *>();
    CYTL::StaticTypeCheckEQ<decltype( CYTL::cend(arr) ), const int *>();
}

TEST_CASE(TypeConvertibility)
{
    static_assert(CYTL::IsTypeSame<int, int>::value == true, "");
    static_assert(CYTL::IsTypeSame<double, int>::value == false, "");

    static_assert(CYTL::IsTypeConvertibile<int, int>::value == true, "");
    static_assert(CYTL::IsTypeConvertibile<double, int>::value == true, "");

    struct P{};
    struct C: P{};

    static_assert(CYTL::IsTypeConvertibile<P, C>::value == false, "");
    static_assert(CYTL::IsTypeConvertibile<C, P>::value == true, "");

    static_assert(CYTL::IsSuperClass<C, C>::value == true, "");
    static_assert(CYTL::IsSuperClass<P, C>::value == true, "");
    static_assert(CYTL::IsSuperClass<C, P>::value == false, "");

    static_assert(CYTL::IsStrictSuperClass<C, C>::value == false, "");
    static_assert(CYTL::IsStrictSuperClass<P, C>::value == true, "");
    static_assert(CYTL::IsStrictSuperClass<C, P>::value == false, "");
}