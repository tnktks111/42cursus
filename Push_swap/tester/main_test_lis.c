// #include "push_swap.h" // LIS関数と関連構造体の宣言
// #include <stdio.h>
// #include <string.h> // strcmpなど (今回は未使用)
// #include <assert.h> // assert (より厳密なテスト用)

// void free_list(t_list_info *info) {
//     if (!info) return;
//     if (info->head && info->size > 0) {
//         t_circ_doubly_list *current = info->head;
//         for (int i = 0; i < info->size; ++i) {
//             t_circ_doubly_list *temp = current;
//             current = current->nxt;
//             free(temp);
//             if (current == info->head && i < info->size -1) { // 既に一周してしまった場合（リストが小さい場合など）
//                 // ただし、この解放ロジックは、info->size 分回ることを前提としているので、
//                 // 循環リストの場合、current == info->headで終了すると、info->sizeと一致しない場合に問題が起こる。
//                 // 正しくは、nextを保存し、一周するまで解放するか、カウンタで管理。
//                 // ここではカウンタで管理しているので、ほぼ問題ないはず。
//             }
//         }
//     }
//     free(info);
// }

// // --- テスト用ヘルパー関数 ---

// t_list_info *create_list_from_array(const int *arr, int size) {
//     if (size < 0) return NULL; // 不正なサイズ

//     t_list_info *info = (t_list_info *)malloc(sizeof(t_list_info));
//     if (!info) {
//         perror("Failed to allocate t_list_info");
//         return NULL;
//     }
//     info->size = size;
//     info->head = NULL;

//     if (size == 0) {
//         return info;
//     }

//     t_circ_doubly_list *head_node = NULL;
//     t_circ_doubly_list *current_node = NULL;
//     t_circ_doubly_list *prev_node = NULL;

//     for (int i = 0; i < size; ++i) {
//         current_node = (t_circ_doubly_list *)malloc(sizeof(t_circ_doubly_list));
//         if (!current_node) {
//             perror("Failed to allocate t_circ_doubly_list node");
//             // ここまでの確保分を解放する（簡略化のため省略、本番では必要）
//             free_list(info); // info->headが途中でも解放試行
//             return NULL;
//         }
//         current_node->content = arr[i];
//         current_node->in_lis = 0; // 初期値は0
//         current_node->nxt = NULL;
//         current_node->prv = prev_node;

//         if (prev_node) {
//             prev_node->nxt = current_node;
//         }
//         if (i == 0) {
//             head_node = current_node;
//         }
//         prev_node = current_node;
//     }

//     if (head_node) { // リストを循環させる
//         head_node->prv = current_node; // current_node は最後のノードのはず
//         current_node->nxt = head_node;
//     }
//     info->head = head_node;
//     return info;
// }



// void print_list_with_lis_flags(t_list_info *info, const char *test_name) {
//     printf("--- Test Case: %s ---\n", test_name);
//     if (!info) {
//         printf("List pointer is NULL.\n");
//         return;
//     }
//     if (info->size == 0 || !info->head) {
//         printf("List is empty (Size: %d, Head: %p).\n", info->size, (void*)info->head);
//         return;
//     }

//     t_circ_doubly_list *current = info->head;
//     printf("  Values:      ");
//     for (int i = 0; i < info->size; ++i) {
//         printf("%4d ", current->content);
//         current = current->nxt;
//     }
//     printf("\n");

//     current = info->head;
//     printf("  LIS Flags:   ");
//     for (int i = 0; i < info->size; ++i) {
//         printf("%4d ", current->in_lis);
//         current = current->nxt;
//     }
//     printf("\n");
// }

// // LISの結果が期待されるパターンと一致するか検証
// int check_lis_pattern(t_list_info *info, const int *expected_pattern, int expected_size) {
//     if (!info) {
//         printf("  Verification FAILED: List info is NULL.\n");
//         return 0;
//     }
//     if (info->size != expected_size) {
//         printf("  Verification FAILED: List size mismatch (Expected: %d, Got: %d).\n", expected_size, info->size);
//         return 0;
//     }
//     if (info->size == 0) return 1; // Empty list matches empty pattern

//     t_circ_doubly_list *current = info->head;
//     for (int i = 0; i < info->size; ++i) {
//         if (current->in_lis != expected_pattern[i]) {
//             printf("  Verification FAILED: LIS flag mismatch at index %d (Value: %d, Expected: %d, Got: %d).\n",
//                    i, current->content, expected_pattern[i], current->in_lis);
//             return 0;
//         }
//         current = current->nxt;
//     }
//     return 1; // All flags match
// }


// typedef struct {
//     const char *name;
//     int arr[20]; // テスト配列の最大サイズを仮定
//     int size;
//     int expected_pattern[20]; // 期待されるin_lisフラグ (0 or 1)
// } TestCase;


// int main() {
//     // テストケース定義
//     TestCase tests[] = {
//         {"Empty list", {}, 0, {}},
//         {"Single element", {5}, 1, {1}},
//         {"All ascending", {10, 20, 30, 40}, 4, {1, 1, 1, 1}},
//         {"All descending (LIS {10})", {40, 30, 20, 10}, 4, {0, 0, 0, 1}},
//         {"Mountain peak (LIS {10,20,30,40})", {10, 20, 50, 30, 40}, 5, {1, 1, 0, 1, 1}}, // LISが{10,20,30,40}の場合
//         {"Valley shape (LIS {10,30,40})", {50, 20, 10, 30, 40}, 5, {0, 0, 1, 1, 1}},
//         {"Repeated elements (LIS {10,20(first),30})", {10, 20, 20, 30}, 4, {1, 1, 0, 1}},
//         {"Standard example (LIS {1,2,4,5})", {10, 1, 2, 11, 3, 4, 5}, 7, {0,1,1,0,1,1,1}},
//         {"Negative numbers (LIS {-5,-2,0,3})", {-5, 10, -2, 0, -10, 3}, 6, {1,0,1,1,0,1}},
//         {"Complex case (LIS {-1,2,3,7,9,10})", {3, 4, -1, 5, 8, 2, 3, 12, 7, 9, 10}, 11, {0,0,1,0,0,1,1,0,1,1,1}},
//     };
//     int num_tests = sizeof(tests) / sizeof(TestCase);
//     int passed_count = 0;

//     printf("===========================================\n");
//     printf("Starting LIS Function Tests\n");
//     printf("===========================================\n");
//     for (int i = 0; i < num_tests; ++i) {
//         t_list_info *info = create_list_from_array(tests[i].arr, tests[i].size);

//         // create_list_from_arrayがNULLを返す場合のチェック
//         if (tests[i].size > 0 && !info) {
//             printf("--- Test Case: %s ---\n", tests[i].name);
//             printf("  Memory allocation FAILED for list creation.\n");
//             printf("  Result: ERROR (SKIPPED)\n\n");
//             continue;
//         }
//          if (tests[i].size == 0 && !(info && info->head == NULL && info->size ==0)) {
//             printf("--- Test Case: %s ---\n", tests[i].name);
//             printf("  Empty list creation FAILED.\n");
//             printf("  Result: ERROR (SKIPPED)\n\n");
//             if(info) free_list(info); // infoがNULLでないなら解放試行
//             continue;
//         }


//         int ret_code = lis(info); // テスト対象のLIS関数を呼び出し

//         print_list_with_lis_flags(info, tests[i].name);

//         if (ret_code == EXIT_FAILURE) {
//             printf("  LIS function returned EXIT_FAILURE.\n");
//             printf("  Result: FAILED (LIS function error)\n");
//         } else {
//             if (check_lis_pattern(info, tests[i].expected_pattern, tests[i].size)) {
//                 printf("  Result: PASSED\n");
//                 passed_count++;
//             } else {
//                 // check_lis_pattern内で失敗理由は表示済み
//                 printf("  Result: FAILED (Pattern mismatch)\n");
//             }
//         }
//         printf("\n");

//         free_list(info);
//     }

//     printf("===========================================\n");
//     printf("Test Summary: %d / %d tests passed.\n", passed_count, num_tests);
//     printf("===========================================\n");

//     return 0;
// }