#include "zroc/error/zroc_error.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdio.h>

Test(zroc_error, set_get_code) {
  zroc_err_set(ZROC_ERR_ALLOC_FAILED, NULL);
  ZrocErr *err = zroc_err_get();
  cr_assert(err->code == ZROC_ERR_ALLOC_FAILED,
            "Error code should be `ZROC_ERR_ALLOC_FAILED`");
}

Test(zroc_error, set_get_default_msg) {
  zroc_err_set(ZROC_ERR_ALLOC_FAILED, NULL);
  ZrocErr *err = zroc_err_get();
  cr_assert_str_eq(err->message, ZROC_ERRORS[ZROC_ERR_ALLOC_FAILED].message);
}

Test(zroc_error, set_get_custom_msg) {
  zroc_err_set(ZROC_ERR_ALLOC_FAILED, "TEST");
  ZrocErr *err = zroc_err_get();
  cr_assert_str_eq(err->message, "TEST", "Error message should be `TEST`");
}
// TODO: Multiple threads with different errors
