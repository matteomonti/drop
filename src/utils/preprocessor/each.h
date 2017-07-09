#if !defined(__forward__) && !defined(__drop__utils__preprocessor__each__h)
#define __drop__utils__preprocessor__each__h

#define utils_reverse 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define utils_count_extract(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...) N

#define utils_nargs_indirect(dummy, ...) utils_count_extract(__VA_ARGS__)
#define utils_nargs(...) utils_nargs_indirect(dummy, ##__VA_ARGS__, utils_reverse)

#define utils_concat(beg, end) utils_concat_indirect(beg, end)
#define utils_concat_indirect(beg, end) beg##end

#define utils_each_0(operation, ...)
#define utils_each_1(operation, suffix, ...) operation(suffix)
#define utils_each_2(operation, suffix, ...) operation(suffix), utils_each_1(operation, __VA_ARGS__)
#define utils_each_3(operation, suffix, ...) operation(suffix), utils_each_2(operation, __VA_ARGS__)
#define utils_each_4(operation, suffix, ...) operation(suffix), utils_each_3(operation, __VA_ARGS__)
#define utils_each_5(operation, suffix, ...) operation(suffix), utils_each_4(operation, __VA_ARGS__)
#define utils_each_6(operation, suffix, ...) operation(suffix), utils_each_5(operation, __VA_ARGS__)
#define utils_each_7(operation, suffix, ...) operation(suffix), utils_each_6(operation, __VA_ARGS__)
#define utils_each_8(operation, suffix, ...) operation(suffix), utils_each_7(operation, __VA_ARGS__)
#define utils_each_9(operation, suffix, ...) operation(suffix), utils_each_8(operation, __VA_ARGS__)
#define utils_each_10(operation, suffix, ...) operation(suffix), utils_each_9(operation, __VA_ARGS__)
#define utils_each_11(operation, suffix, ...) operation(suffix), utils_each_10(operation, __VA_ARGS__)
#define utils_each_12(operation, suffix, ...) operation(suffix), utils_each_11(operation, __VA_ARGS__)
#define utils_each_13(operation, suffix, ...) operation(suffix), utils_each_12(operation, __VA_ARGS__)
#define utils_each_14(operation, suffix, ...) operation(suffix), utils_each_13(operation, __VA_ARGS__)
#define utils_each_15(operation, suffix, ...) operation(suffix), utils_each_14(operation, __VA_ARGS__)
#define utils_each_16(operation, suffix, ...) operation(suffix), utils_each_15(operation, __VA_ARGS__)

#define utils_each(operation, ...) utils_concat(utils_each_, utils_nargs(__VA_ARGS__))(operation, __VA_ARGS__)

#endif
