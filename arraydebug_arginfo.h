/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 86ad7e8c6334a6ab1197df6a41e0a7a82074bd11 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_array_debuginfo, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, array, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_array_hash_distribution arginfo_array_debuginfo

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_array_load_factor, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, array, IS_ARRAY, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(array_debuginfo);
ZEND_FUNCTION(array_hash_distribution);
ZEND_FUNCTION(array_load_factor);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(array_debuginfo, arginfo_array_debuginfo)
	ZEND_FE(array_hash_distribution, arginfo_array_hash_distribution)
	ZEND_FE(array_load_factor, arginfo_array_load_factor)
	ZEND_FE_END
};
