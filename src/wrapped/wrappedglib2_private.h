#if !(defined(GO) && defined(GOM) && defined(GO2) && defined(DATA))
#error meh!
#endif

//GO(__aeabi_d2lz, 
//GO(__aeabi_d2ulz, 
//GO(_fini, 
GO(g_access, iFpi)
GO(g_allocator_free, vFp)
GO(g_allocator_new, pFpu)
GO(g_array_append_vals, pFppu)
GO(g_array_free, pFpi)
GO(g_array_get_element_size, uFp)
GO(g_array_insert_vals, pFpupu)
GO(g_array_new, pFiiu)
GO(g_array_prepend_vals, pFppu)
GO(g_array_ref, pFp)
GO(g_array_remove_index, pFpu)
GO(g_array_remove_index_fast, pFpu)
GO(g_array_remove_range, pFpuu)
GOM(g_array_set_clear_func, vFEpp)
GO(g_array_set_size, pFpu)
GO(g_array_sized_new, pFiiuu)
GOM(g_array_sort, vFEpp)
GOM(g_array_sort_with_data, vFEppp)
GO(g_array_unref, vFp)
GO(g_ascii_digit_value, iFC)
GO(g_ascii_dtostr, pFpid)
GO(g_ascii_formatd, pFpipd)
GO(g_ascii_strcasecmp, iFpp)
GO(g_ascii_strdown, pFpi)
GO(g_ascii_strncasecmp, iFppu)
GO(g_ascii_strtod, dFpp)
GO(g_ascii_strtoll, IFppu)
GO(g_ascii_strtoull, UFppu)
GO(g_ascii_strup, pFpi)
GO(g_ascii_tolower, CFC)
GO(g_ascii_toupper, CFC)
GO(g_ascii_xdigit_value, iFC)
GO(g_assertion_message, vFppipp)
#ifdef HAVE_LD80BITS
GO(g_assertion_message_cmpnum, vFppippDDC)
#else
GO(g_assertion_message_cmpnum, vFppippKKC)
#endif
GO(g_assertion_message_cmpstr, vFppippppp)
GO(g_assertion_message_error, vFppipppui)
GO(g_assertion_message_expr, vFppipp)
GO(g_assert_warning, vFppipp)
GO(g_async_queue_length, iFp)
//GO(g_async_queue_length_unlocked, 
GO(g_async_queue_lock, vFp)
GO(g_async_queue_new, pFv)
//GO(g_async_queue_new_full, 
GO(g_async_queue_pop, pFp)
//GO(g_async_queue_pop_unlocked, 
GO(g_async_queue_push, vFpp)
//GO(g_async_queue_push_sorted, 
//GO(g_async_queue_push_sorted_unlocked, 
GO(g_async_queue_push_unlocked, vFpp)
GO(g_async_queue_ref, vFp)
//GO(g_async_queue_ref_unlocked, 
//GO(g_async_queue_sort, 
//GO(g_async_queue_sort_unlocked, 
//GO(g_async_queue_timed_pop, 
//GO(g_async_queue_timed_pop_unlocked, 
GO(g_async_queue_timeout_pop, pFpU)
GO(g_async_queue_timeout_pop_unlocked, pFpU)
GO(g_async_queue_try_pop, pFp)
GO(g_async_queue_try_pop_unlocked, pFp)
GO(g_async_queue_unlock, vFp)
GO(g_async_queue_unref, vFp)
GO(g_async_queue_unref_and_unlock, vFp)
GO2(g_atexit, vFEp, my_atexit)
//GO(g_atomic_int_add, 
//GO(g_atomic_int_and, 
//GO(g_atomic_int_compare_and_exchange, 
//GO(g_atomic_int_dec_and_test, 
//GO(g_atomic_int_exchange_and_add, 
//GO(g_atomic_int_get, 
//GO(g_atomic_int_inc, 
//GO(g_atomic_int_or, 
//GO(g_atomic_int_set, 
//GO(g_atomic_int_xor, 
//GO(g_atomic_pointer_add, 
//GO(g_atomic_pointer_and, 
//GO(g_atomic_pointer_compare_and_exchange, 
//GO(g_atomic_pointer_get, 
//GO(g_atomic_pointer_or, 
//GO(g_atomic_pointer_set, 
//GO(g_atomic_pointer_xor, 
GO(g_base64_decode, pFpp)
GO(g_base64_decode_inplace, pFpp)
GO(g_base64_decode_step, LFpLppp)
GO(g_base64_encode, pFpL)
GO(g_base64_encode_close, LFippp)
GO(g_base64_encode_step, LFpLippp)
GO(g_basename, pFp)
//GO(g_bit_lock, 
GO(g_bit_nth_lsf, iFii)
GO(g_bit_nth_msf, iFii)
GO(g_bit_storage, iFi)
//GO(g_bit_trylock, 
//GO(g_bit_unlock, 
//GO(g_blow_chunks, 
//GO(g_bookmark_file_add_application, 
//GO(g_bookmark_file_add_group, 
//GO(g_bookmark_file_error_quark, 
//GO(g_bookmark_file_free, 
//GO(g_bookmark_file_get_added, 
//GO(g_bookmark_file_get_app_info, 
//GO(g_bookmark_file_get_applications, 
//GO(g_bookmark_file_get_description, 
//GO(g_bookmark_file_get_groups, 
//GO(g_bookmark_file_get_icon, 
//GO(g_bookmark_file_get_is_private, 
//GO(g_bookmark_file_get_mime_type, 
//GO(g_bookmark_file_get_modified, 
//GO(g_bookmark_file_get_size, 
//GO(g_bookmark_file_get_title, 
//GO(g_bookmark_file_get_uris, 
//GO(g_bookmark_file_get_visited, 
//GO(g_bookmark_file_has_application, 
//GO(g_bookmark_file_has_group, 
//GO(g_bookmark_file_has_item, 
//GO(g_bookmark_file_load_from_data, 
//GO(g_bookmark_file_load_from_data_dirs, 
//GO(g_bookmark_file_load_from_file, 
//GO(g_bookmark_file_move_item, 
//GO(g_bookmark_file_new, 
//GO(g_bookmark_file_remove_application, 
//GO(g_bookmark_file_remove_group, 
//GO(g_bookmark_file_remove_item, 
//GO(g_bookmark_file_set_added, 
//GO(g_bookmark_file_set_app_info, 
//GO(g_bookmark_file_set_description, 
//GO(g_bookmark_file_set_groups, 
//GO(g_bookmark_file_set_icon, 
//GO(g_bookmark_file_set_is_private, 
//GO(g_bookmark_file_set_mime_type, 
//GO(g_bookmark_file_set_modified, 
//GO(g_bookmark_file_set_title, 
//GO(g_bookmark_file_set_visited, 
//GO(g_bookmark_file_to_data, 
//GO(g_bookmark_file_to_file, 
GOM(g_build_filename, pFEpV)
GO(g_build_filenamev, pFp)
//GOM(g_build_path, pFEppV) // wrap using g_build_pathv
GO(g_build_pathv, pFpp)
GO(g_byte_array_append, pFppu)
GO(g_byte_array_free, pFpi)
GO(g_byte_array_free_to_bytes, pFp)
GO(g_byte_array_new, pFv)
GO(g_byte_array_new_take, pFpL)
GO(g_byte_array_prepend, pFppu)
GO(g_byte_array_ref, pFp)
GO(g_byte_array_remove_index, pFpu)
GO(g_byte_array_remove_index_fast, pFpu)
GO(g_byte_array_remove_range, pFpuu)
GO(g_byte_array_set_size, pFpu)
GO(g_byte_array_sized_new, pFu)
//GOM(g_byte_array_sort, vFpB)
//GOM(g_byte_array_sort_with_data, vFpBp)
GO(g_byte_array_unref, vFp)
GO(g_bytes_compare, iFpp)
GO(g_bytes_equal, iFpp)
GO(g_bytes_get_data, pFpL)
GO(g_bytes_get_size, LFp)
GO(g_bytes_hash, uFp)
GO(g_bytes_new, pFpL)
GO(g_bytes_new_from_bytes, pFpLL)
GO(g_bytes_new_static, pFpL)
GO(g_bytes_new_take, pFpL)
//GOM(g_bytes_new_with_free_func, pFppLBp)
GO(g_bytes_ref, pFp)
GO(g_bytes_unref, vFp)
GO(g_bytes_unref_to_array, pFp)
GO(g_bytes_unref_to_data, pFpp)
//GO(g_cache_destroy, 
//GO(g_cache_insert, 
//GO(g_cache_key_foreach, 
//GO(g_cache_new, 
//GO(g_cache_remove, 
//GO(g_cache_value_foreach, 
GO(g_chdir, iFp)
//GO(g_checksum_copy, 
//GO(g_checksum_free, 
//GO(g_checksum_get_digest, 
//GO(g_checksum_get_string, 
//GO(g_checksum_new, 
//GO(g_checksum_reset, 
//GO(g_checksum_type_get_length, 
//GO(g_checksum_update, 
GOM(g_child_watch_add, uFEipp)
GOM(g_child_watch_add_full, uFEiippp)
GO(g_child_watch_source_new, pFi)
GO(g_chmod, iFpi)
GO(g_clear_error, vFp)
//GOM(g_clear_pointer, vFEpp)
GO(g_close, iFip)
//GO(g_completion_add_items, 
//GO(g_completion_clear_items, 
//GO(g_completion_complete, 
//GO(g_completion_complete_utf8, 
//GO(g_completion_free, 
//GO(g_completion_new, 
//GO(g_completion_remove_items, 
//GO(g_completion_set_compare, 
//GO(g_compute_checksum_for_bytes, 
//GO(g_compute_checksum_for_data, 
//GO(g_compute_checksum_for_string, 
//GO(g_compute_hmac_for_data, 
//GO(g_compute_hmac_for_string, 
//GO(g_cond_broadcast, 
//GO(g_cond_clear, 
GO(g_cond_free, vFp)
//GO(g_cond_init, 
GO(g_cond_new, pFv)
//GO(g_cond_signal, 
//GO(g_cond_timed_wait, 
//GO(g_cond_wait, 
//GO(g_cond_wait_until, 
GO(g_convert, pFplppppp)
//GO(g_convert_error_quark, 
GO(g_convert_with_fallback, pFplpppppp)
GO(g_convert_with_iconv, pFplpppp)
GO(g_creat, iFpi)
GO(g_datalist_clear, vFp)
//GOM(g_datalist_foreach, vFEppp)
GO(g_datalist_get_data, pFpp)
GO(g_datalist_get_flags, uFp)
GOM(g_datalist_id_dup_data, pFEpupp)
GO(g_datalist_id_get_data, pFpu)
GO(g_datalist_id_remove_no_notify, pFpu)
GOM(g_datalist_id_replace_data, iFEpupppp)
GOM(g_datalist_id_set_data_full, vFEpupp)
GO(g_datalist_init, vFp)
GO(g_datalist_set_flags, vFpu)
GO(g_datalist_unset_flags, vFpu)
//GO(g_dataset_destroy, 
//GO(g_dataset_foreach, 
//GO(g_dataset_id_get_data, 
//GO(g_dataset_id_remove_no_notify, 
//GO(g_dataset_id_set_data_full, 
GO(g_date_add_days, vFpu)
GO(g_date_add_months, vFpu)
GO(g_date_add_years, vFpu)
GO(g_date_clamp, vFppp)
GO(g_date_clear, vFpu)
GO(g_date_compare, iFpp)
GO(g_date_days_between, iFpp)
GO(g_date_free, vFp)
GO(g_date_get_day, CFp)
GO(g_date_get_day_of_year, uFp)
GO(g_date_get_days_in_month, CFip)
GO(g_date_get_iso8601_week_of_year, uFp)
GO(g_date_get_julian, uFp)
GO(g_date_get_monday_week_of_year, uFp)
GO(g_date_get_monday_weeks_in_year, CFp)
GO(g_date_get_month, iFp)
GO(g_date_get_sunday_week_of_year, uFp)
GO(g_date_get_sunday_weeks_in_year, CFp)
GO(g_date_get_weekday, iFp)
GO(g_date_get_year, WFp)
GO(g_date_is_first_of_month, iFp)
GO(g_date_is_last_of_month, iFp)
GO(g_date_is_leap_year, iFp)
GO(g_date_new, pFv)
GO(g_date_new_dmy, pFCiW)
GO(g_date_new_julian, pFu)
GO(g_date_order, vFpp)
GO(g_date_set_day, vFpC)
GO(g_date_set_dmy, vFpCiW)
GO(g_date_set_julian, vFpu)
GO(g_date_set_month, vFpi)
GO(g_date_set_parse, vFpp)
GO(g_date_set_time, vFpi)
//GO(g_date_set_time_t, 
GO(g_date_set_time_val, vFpp)
GO(g_date_set_year, vFpW)
GO(g_date_strftime, LFpLpp)
GO(g_date_subtract_days, vFpu)
GO(g_date_subtract_months, vFpu)
GO(g_date_subtract_years, vFpu)
//GO(g_date_time_add, 
//GO(g_date_time_add_days, 
//GO(g_date_time_add_full, 
//GO(g_date_time_add_hours, 
//GO(g_date_time_add_minutes, 
//GO(g_date_time_add_months, 
//GO(g_date_time_add_seconds, 
//GO(g_date_time_add_weeks, 
//GO(g_date_time_add_years, 
//GO(g_date_time_compare, 
//GO(g_date_time_difference, 
//GO(g_date_time_equal, 
//GO(g_date_time_format, 
//GO(g_date_time_get_day_of_month, 
//GO(g_date_time_get_day_of_week, 
//GO(g_date_time_get_day_of_year, 
//GO(g_date_time_get_hour, 
//GO(g_date_time_get_microsecond, 
//GO(g_date_time_get_minute, 
//GO(g_date_time_get_month, 
//GO(g_date_time_get_second, 
//GO(g_date_time_get_seconds, 
//GO(g_date_time_get_timezone_abbreviation, 
//GO(g_date_time_get_utc_offset, 
//GO(g_date_time_get_week_numbering_year, 
//GO(g_date_time_get_week_of_year, 
//GO(g_date_time_get_year, 
//GO(g_date_time_get_ymd, 
//GO(g_date_time_hash, 
//GO(g_date_time_is_daylight_savings, 
//GO(g_date_time_new, 
//GO(g_date_time_new_from_timeval_local, 
//GO(g_date_time_new_from_timeval_utc, 
//GO(g_date_time_new_from_unix_local, 
//GO(g_date_time_new_from_unix_utc, 
//GO(g_date_time_new_local, 
//GO(g_date_time_new_now, 
//GO(g_date_time_new_now_local, 
//GO(g_date_time_new_now_utc, 
//GO(g_date_time_new_utc, 
//GO(g_date_time_ref, 
//GO(g_date_time_to_local, 
//GO(g_date_time_to_timeval, 
//GO(g_date_time_to_timezone, 
//GO(g_date_time_to_unix, 
//GO(g_date_time_to_utc, 
//GO(g_date_time_unref, 
GO(g_date_to_struct_tm, vFpp)
GO(g_date_valid, iFp)
GO(g_date_valid_day, iFC)
GO(g_date_valid_dmy, iFCiW)
GO(g_date_valid_julian, iFu)
GO(g_date_valid_month, iFi)
GO(g_date_valid_weekday, iFi)
GO(g_date_valid_year, iFW)
GO(g_dcgettext, pFppi)
GO(g_dgettext, pFpp)
GO(g_dir_close, vFp)
GO(g_direct_equal, iFpp)
GO(g_direct_hash, uFp)
GO(g_dir_make_tmp, pFpp)
GO(g_dir_open, pFp)
//GO(g_dir_read_name, 
GO(g_dir_rewind, vFp)
GO(g_dngettext, pFpppL)
GO(g_double_equal, iFpp)
GO(g_double_hash, uFp)
GO(g_dpgettext, pFppL)
GO(g_dpgettext2, pFppp)
GO(g_environ_getenv, pFpp)      // should wrap?
GO(g_environ_setenv, pFpppi)
GO(g_environ_unsetenv, pFpp)
GO(g_error_copy, pFp)
GO(g_error_free, vFp)
GO(g_error_matches, iFppi)
GO2(g_error_new, pFpipV, g_error_new_valist)
GO(g_error_new_literal, pFpip)
GO(g_error_new_valist, pFpipp)
GO(g_file_error_from_errno, iFi)
GO(g_file_error_quark, pFv)
GO(g_file_get_contents, iFpppp)
GO(g_filename_display_basename, pFp)
GO(g_filename_display_name, pFp)
GO(g_filename_from_uri, pFppp)
GO(g_filename_from_utf8, pFpippp)
GO(g_filename_to_uri, pFppp)
GO(g_filename_to_utf8, pFpippp)
GO(g_file_open_tmp, iFppp)
GO(g_file_read_link, pFpp)
GO(g_file_set_contents, iFppip)
GO(g_file_test, iFpi)
GO(g_find_program_in_path, pFp) // need wrap?
GO(g_fopen, pFpp)
GO(g_format_size, pFU)
GO(g_format_size_for_display, pFI)
GO(g_format_size_full, pFUi)
GO2(g_fprintf, iFEppV, my_g_vfprintf)
GO(g_free, vFp)
GO(g_freopen, pFppp)
GO(g_get_application_name, pFv)
GO(g_get_charset, iFp)
GO(g_get_codeset, pFv)
GO(g_get_current_dir, pFv)
GO(g_get_current_time, vFp)
GO(g_getenv, pFp)       // should wrap?
GO(g_get_environ, pFv)
GO(g_get_filename_charsets, iFp)
GO(g_get_home_dir, pFv)
GO(g_get_host_name, pFv)
GO(g_get_language_names, pFv)
GO(g_get_locale_variants, pFp)
GO(g_get_monotonic_time, IFv)
//GO(g_get_num_processors, 
GO(g_get_prgname, pFv)
GO(g_get_real_name, pFv)
GO(g_get_real_time, IFv)
GO(g_get_system_config_dirs, pFv)
GO(g_get_system_data_dirs, pFv)
GO(g_get_tmp_dir, pFv)
GO(g_get_user_cache_dir, pFv)
GO(g_get_user_config_dir, pFv)
GO(g_get_user_data_dir, pFv)
GO(g_get_user_name, pFv)
GO(g_get_user_runtime_dir, pFv)
GO(g_get_user_special_dir, pFi)
GO(g_hash_table_add, iFpp)
GO(g_hash_table_contains, iFpp)
GO(g_hash_table_destroy, vFp)
GOM(g_hash_table_find, pFEppp)
GOM(g_hash_table_foreach, vFEppp)
GOM(g_hash_table_foreach_remove, uFEppp)
GOM(g_hash_table_foreach_steal, uFEppp)
GO(g_hash_table_get_keys, pFp)
GO(g_hash_table_get_keys_as_array, pFpp)
GO(g_hash_table_get_values, pFp)
GO(g_hash_table_insert, iFppp)
GO(g_hash_table_iter_get_hash_table, pFp)
GO(g_hash_table_iter_init, vFpp)
GO(g_hash_table_iter_next, iFppp)
GO(g_hash_table_iter_remove, vFp)
GO(g_hash_table_iter_replace, vFpp)
GO(g_hash_table_iter_steal, vFp)
GO(g_hash_table_lookup, pFpp)
GO(g_hash_table_lookup_extended, iFpppp)
GOM(g_hash_table_new, pFEpp)
GOM(g_hash_table_new_full, pFEpppp)
GO(g_hash_table_ref, pFp)
GO(g_hash_table_remove, iFpp)
GO(g_hash_table_remove_all, vFp)
GO(g_hash_table_replace, iFppp)
GO(g_hash_table_size, uFp)
GO(g_hash_table_steal, iFpp)
GO(g_hash_table_steal_all, vFp)
GO(g_hash_table_unref, vFp)
//GO(g_hmac_copy, 
//GO(g_hmac_get_digest, 
//GO(g_hmac_get_string, 
//GO(g_hmac_new, 
//GO(g_hmac_ref, 
//GO(g_hmac_unref, 
//GO(g_hmac_update, 
//GO(g_hook_alloc, 
//GO(g_hook_compare_ids, 
//GO(g_hook_destroy, 
//GO(g_hook_destroy_link, 
//GO(g_hook_find, 
//GO(g_hook_find_data, 
//GO(g_hook_find_func, 
//GO(g_hook_find_func_data, 
//GO(g_hook_first_valid, 
//GO(g_hook_free, 
//GO(g_hook_get, 
//GO(g_hook_insert_before, 
//GO(g_hook_insert_sorted, 
//GO(g_hook_list_clear, 
//GO(g_hook_list_init, 
//GO(g_hook_list_invoke, 
//GO(g_hook_list_invoke_check, 
//GO(g_hook_list_marshal, 
//GO(g_hook_list_marshal_check, 
//GO(g_hook_next_valid, 
//GO(g_hook_prepend, 
//GO(g_hook_ref, 
//GO(g_hook_unref, 
//GO(g_hostname_is_ascii_encoded, 
//GO(g_hostname_is_ip_address, 
//GO(g_hostname_is_non_ascii, 
//GO(g_hostname_to_ascii, 
//GO(g_hostname_to_unicode, 
GO(g_iconv, LFppppp)
GO(g_iconv_close, iFp)
GO(g_iconv_open, pFpp)
GOM(g_idle_add, uFEpp)
GOM(g_idle_add_full, uFEippp)
GO(g_idle_remove_by_data, iFp)
GO(g_idle_source_new, pFv)
GO(g_int64_equal, iFpp)
GO(g_int64_hash, uFp)
GO(g_int_equal, iFpp)
GO(g_intern_static_string, pFp)
GO(g_intern_string, pFp)
GO(g_int_hash, uFp)
//GO(g_io_add_watch, 
//GO(g_io_add_watch_full, 
//GO(g_io_channel_close, 
//GO(g_io_channel_error_from_errno, 
//GO(g_io_channel_error_quark, 
//GO(g_io_channel_flush, 
//GO(g_io_channel_get_buffer_condition, 
//GO(g_io_channel_get_buffered, 
//GO(g_io_channel_get_buffer_size, 
//GO(g_io_channel_get_close_on_unref, 
//GO(g_io_channel_get_encoding, 
//GO(g_io_channel_get_flags, 
//GO(g_io_channel_get_line_term, 
//GO(g_io_channel_init, 
//GO(g_io_channel_new_file, 
//GO(g_io_channel_read, 
//GO(g_io_channel_read_chars, 
//GO(g_io_channel_read_line, 
//GO(g_io_channel_read_line_string, 
//GO(g_io_channel_read_to_end, 
//GO(g_io_channel_read_unichar, 
//GO(g_io_channel_ref, 
//GO(g_io_channel_seek, 
//GO(g_io_channel_seek_position, 
//GO(g_io_channel_set_buffered, 
//GO(g_io_channel_set_buffer_size, 
//GO(g_io_channel_set_close_on_unref, 
//GO(g_io_channel_set_encoding, 
//GO(g_io_channel_set_flags, 
//GO(g_io_channel_set_line_term, 
//GO(g_io_channel_shutdown, 
//GO(g_io_channel_unix_get_fd, 
//GO(g_io_channel_unix_new, 
//GO(g_io_channel_unref, 
//GO(g_io_channel_write, 
//GO(g_io_channel_write_chars, 
//GO(g_io_channel_write_unichar, 
//GO(g_io_create_watch, 
GO(g_key_file_error_quark, pFv)
GO(g_key_file_free, vFp)
GO(g_key_file_get_boolean, iFpppp)
GO(g_key_file_get_boolean_list, pFppppp)
GO(g_key_file_get_comment, pFpppp)
GO(g_key_file_get_double, dFpppp)
GO(g_key_file_get_double_list, pFppppp)
GO(g_key_file_get_groups, pFpp)
GO(g_key_file_get_int64, IFpppp)
GO(g_key_file_get_integer, iFpppp)
GO(g_key_file_get_integer_list, pFppppp)
GO(g_key_file_get_keys, pFpppp)
GO(g_key_file_get_locale_string, pFppppp)
GO(g_key_file_get_locale_string_list, pFpppppp)
GO(g_key_file_get_start_group, pFp)
GO(g_key_file_get_string, pFpppp)
GO(g_key_file_get_string_list, pFppppp)
GO(g_key_file_get_uint64, UFpppp)
GO(g_key_file_get_value, pFpppp)
GO(g_key_file_has_group, iFpp)
GO(g_key_file_has_key, iFpppp)
GO(g_key_file_load_from_data, iFppLip)
GO(g_key_file_load_from_data_dirs, iFpppip)
GO(g_key_file_load_from_dirs, iFppppip)
GO(g_key_file_load_from_file, iFppip)
GO(g_key_file_new, pFv)
GO(g_key_file_ref, pFp)
GO(g_key_file_remove_comment, iFpppp)
GO(g_key_file_remove_group, iFppp)
GO(g_key_file_remove_key, iFpppp)
GO(g_key_file_save_to_file, iFppp)
GO(g_key_file_set_boolean, vFpppi)
GO(g_key_file_set_boolean_list, vFppppL)
GO(g_key_file_set_comment, iFppppp)
GO(g_key_file_set_double, vFpppd)
GO(g_key_file_set_double_list, vFppppL)
GO(g_key_file_set_int64, vFpppI)
GO(g_key_file_set_integer, vFpppi)
GO(g_key_file_set_integer_list, vFppppL)
GO(g_key_file_set_list_separator, vFpC)
GO(g_key_file_set_locale_string, vFppppp)
GO(g_key_file_set_locale_string_list, vFpppppL)
GO(g_key_file_set_string, vFpppp)
GO(g_key_file_set_string_list, vFppppL)
GO(g_key_file_set_uint64, vFpppU)
GO(g_key_file_set_value, vFpppp)
GO(g_key_file_to_data, pFppp)
GO(g_key_file_unref, vFp)
//GO(glib_check_version, 
//GO(glib_gettext, 
//GO(glib_pgettext, 
//GO(glib__private__, 
GO(g_list_alloc, pFv)
GO(g_list_append, pFpp)
GO(g_list_concat, pFpp)
GO(g_list_copy, pFp)
//GOM(g_list_copy_deep, pFEpBp)
GO(g_list_delete_link, pFpp)
GO(g_listenv, pFv)
GO(g_list_find, pFpp)
//GOM(g_list_find_custom, pFEppB)
GO(g_list_first, pFp)
//GOM(g_list_foreach, vFEpBp)
GO(g_list_free, vFp)
GO(g_list_free_1, vFp)
GOM(g_list_free_full, vFEpp)
GO(g_list_index, iFpp)
GO(g_list_insert, pFppi)
GO(g_list_insert_before, pFppp)
//GOM(g_list_insert_sorted, pFEppB)
//GO(g_list_insert_sorted_with_data, pFEppBp)
GO(g_list_last, pFp)
GO(g_list_length, uFp)
GO(g_list_nth, pFpu)
GO(g_list_nth_data, pFpu)
GO(g_list_nth_prev, pFpu)
//GO(g_list_pop_allocator, 
GO(g_list_position, iFpp)
GO(g_list_prepend, pFpp)
//GO(g_list_push_allocator, 
GO(g_list_remove, pFpp)
GO(g_list_remove_all, pFpp)
GO(g_list_remove_link, pFpp)
GO(g_list_reverse, pFp)
//GOM(g_list_sort, pFEpB)
//GOM(g_list_sort_with_data, pFEpBp)
GO(g_locale_from_utf8, pFplppp)
GO(g_locale_to_utf8, pFplppp)
GO2(g_log, vFpppV, g_logv)
GO(g_log_default_handler, vFpipp)
GO(g_log_remove_handler, vFpu)
GO(g_log_set_always_fatal, iFi)
//GOM(g_log_set_default_handler, pFEBp)
GO(g_log_set_fatal_mask, iFpi)
//GOM(g_log_set_handler, uFpiBp)
GO(g_logv, vFpppp)      // need align?
GO(g_lstat, iFpp)
GO(g_main_context_acquire, iFp)
GO(g_main_context_add_poll, vFppi)
GO(g_main_context_check, iFpipi)
GO(g_main_context_default, pFv)
GO(g_main_context_dispatch, vFp)
//GOM(g_main_context_find_source_by_funcs_user_data, pFEppp)   // 2nd is a GSourceFuncs structures with callbacks..
GO(g_main_context_find_source_by_id, pFpu)
GO(g_main_context_find_source_by_user_data, pFpp)
GOM(g_main_context_get_poll_func, pFEp)
GO(g_main_context_get_thread_default, pFv)
//GOM(g_main_context_invoke, vFppp)  // 2nd is GSourceFuncs
//GOM(g_main_context_invoke_full, vFpippB)  // 3rd is GSourceFuncs
GO(g_main_context_is_owner, iFp)
GO(g_main_context_iteration, iFpi)
GO(g_main_context_new, pFv)
GO(g_main_context_pending, iFp)
GO(g_main_context_pop_thread_default, vFp)
GO(g_main_context_prepare, iFpp)
GO(g_main_context_push_thread_default, vFp)
GO(g_main_context_query, iFpippi)
GO(g_main_context_ref, pFp)
GO(g_main_context_ref_thread_default, pFv)
GO(g_main_context_release, vFp)
GO(g_main_context_remove_poll, vFpp)
GOM(g_main_context_set_poll_func, vFEpp)
GO(g_main_context_unref, vFp)
GO(g_main_context_wait, iFppp)
GO(g_main_context_wakeup, vFp)
GO(g_main_current_source, pFv)
GO(g_main_depth, iFv)
GO(g_main_loop_get_context, pFp)
GO(g_main_loop_is_running, iFp)
GO(g_main_loop_new, pFpi)
GO(g_main_loop_quit, vFp)
GO(g_main_loop_ref, pFp)
GO(g_main_loop_run, vFp)
GO(g_main_loop_unref, vFp)
GO(g_malloc, pFL)
GO(g_malloc0, pFL)
GO(g_malloc0_n, pFLL)
GO(g_malloc_n, pFLL)
GO(g_mapped_file_free, vFp)
GO(g_mapped_file_get_bytes, pFp)
GO(g_mapped_file_get_contents, pFp)
GO(g_mapped_file_get_length, uFp)
GO(g_mapped_file_new, pFppp)
GO(g_mapped_file_new_from_fd, pFiip)
GO(g_mapped_file_ref, pFp)
GO(g_mapped_file_unref, vFp)
//GO(g_markup_collect_attributes, 
//GO(g_markup_error_quark, 
GO(g_markup_escape_text, pFpl)
//GO(g_markup_parse_context_end_parse, 
//GO(g_markup_parse_context_free, 
//GO(g_markup_parse_context_get_element, 
//GO(g_markup_parse_context_get_element_stack, 
//GO(g_markup_parse_context_get_position, 
//GO(g_markup_parse_context_get_user_data, 
//GO(g_markup_parse_context_new, 
//GO(g_markup_parse_context_parse, 
//GO(g_markup_parse_context_pop, 
//GO(g_markup_parse_context_push, 
//GO(g_markup_parse_context_ref, 
//GO(g_markup_parse_context_unref, 
GOM(g_markup_printf_escaped, pFEpV)
GOM(g_markup_vprintf_escaped, pFEpp)
//GO(g_match_info_expand_references, 
//GO(g_match_info_fetch, 
//GO(g_match_info_fetch_all, 
//GO(g_match_info_fetch_named, 
//GO(g_match_info_fetch_named_pos, 
//GO(g_match_info_fetch_pos, 
//GO(g_match_info_free, 
//GO(g_match_info_get_match_count, 
//GO(g_match_info_get_regex, 
//GO(g_match_info_get_string, 
//GO(g_match_info_is_partial_match, 
//GO(g_match_info_matches, 
//GO(g_match_info_next, 
//GO(g_match_info_ref, 
//GO(g_match_info_unref, 
//GO(g_mem_chunk_alloc, 
//GO(g_mem_chunk_alloc0, 
//GO(g_mem_chunk_clean, 
//GO(g_mem_chunk_destroy, 
//GO(g_mem_chunk_free, 
//GO(g_mem_chunk_info, 
//GO(g_mem_chunk_new, 
//GO(g_mem_chunk_print, 
//GO(g_mem_chunk_reset, 
GO(g_memdup, pFpu)
GO(g_mem_is_system_malloc, iFv)
GO(g_mem_profile, vFv)
//GOM(g_mem_set_vtable, vFEp)   // VMemTable needs wrapping
GO(g_mkdir, iFpi)
GO(g_mkdir_with_parents, iFpi)
GO(g_mkdtemp, pFp)
GO(g_mkdtemp_full, pFpi)
GO(g_mkstemp, iFp)
GO(g_mkstemp_full, iFpii)
GO(g_mutex_clear, vFp)
GO(g_mutex_free, vFp)
GO(g_mutex_init, vFp)
GO(g_mutex_lock, vFp)
GO(g_mutex_new, pFv)
GO(g_mutex_trylock, iFp)
GO(g_mutex_unlock, vFp)
//GO(g_node_child_index, 
//GO(g_node_child_position, 
//GO(g_node_children_foreach, 
//GO(g_node_copy, 
//GO(g_node_copy_deep, 
//GO(g_node_depth, 
//GO(g_node_destroy, 
//GO(g_node_find, 
//GO(g_node_find_child, 
//GO(g_node_first_sibling, 
//GO(g_node_get_root, 
//GO(g_node_insert, 
//GO(g_node_insert_after, 
//GO(g_node_insert_before, 
//GO(g_node_is_ancestor, 
//GO(g_node_last_child, 
//GO(g_node_last_sibling, 
//GO(g_node_max_height, 
//GO(g_node_n_children, 
//GO(g_node_new, 
//GO(g_node_n_nodes, 
//GO(g_node_nth_child, 
//GO(g_node_pop_allocator, 
//GO(g_node_prepend, 
//GO(g_node_push_allocator, 
//GO(g_node_reverse_children, 
//GO(g_node_traverse, 
//GO(g_node_unlink, 
GO(g_nullify_pointer, vFp)
//GO(g_once_impl, 
GO(g_once_init_enter, iFp)
//GO(g_once_init_enter_impl, 
GO(g_once_init_leave, vFpL)
GO(g_on_error_query, vFp)
GO(g_on_error_stack_trace, vFp)
GO(g_open, iFpii)
//GO(g_option_context_add_group, 
//GO(g_option_context_add_main_entries, 
//GO(g_option_context_free, 
//GO(g_option_context_get_description, 
//GO(g_option_context_get_help, 
//GO(g_option_context_get_help_enabled, 
//GO(g_option_context_get_ignore_unknown_options, 
//GO(g_option_context_get_main_group, 
//GO(g_option_context_get_summary, 
//GO(g_option_context_new, 
//GO(g_option_context_parse, 
//GO(g_option_context_parse_strv, 
//GO(g_option_context_set_description, 
//GO(g_option_context_set_help_enabled, 
//GO(g_option_context_set_ignore_unknown_options, 
//GO(g_option_context_set_main_group, 
//GO(g_option_context_set_summary, 
//GO(g_option_context_set_translate_func, 
//GO(g_option_context_set_translation_domain, 
//GO(g_option_error_quark, 
//GO(g_option_group_add_entries, 
//GO(g_option_group_free, 
//GO(g_option_group_new, 
//GO(g_option_group_set_error_hook, 
//GO(g_option_group_set_parse_hooks, 
//GO(g_option_group_set_translate_func, 
//GO(g_option_group_set_translation_domain, 
GO(g_parse_debug_string, uFppi)
GO(g_path_get_basename, pFp)
GO(g_path_get_dirname, pFp)
GO(g_path_is_absolute, iFp)
GO(g_path_skip_root, pFp)
//GO(g_pattern_match, 
//GO(g_pattern_match_simple, 
//GO(g_pattern_match_string, 
//GO(g_pattern_spec_equal, 
//GO(g_pattern_spec_free, 
//GO(g_pattern_spec_new, 
//GO(g_pointer_bit_lock, 
//GO(g_pointer_bit_trylock, 
//GO(g_pointer_bit_unlock, 
GO(g_poll, iFpui)
GO(g_prefix_error, vFpppppppppp)    //vaarg, should align?
GOM(g_print, vFEpV)
GOM(g_printerr, vFEpV)
GO2(g_printf, iFEpV, my_g_vprintf)
GOM(g_printf_string_upper_bound, uFEpp)
GO(g_private_get, pFp)
GOM(g_private_new, pFEp)
GO(g_private_replace, vFpp)
GO(g_private_set, vFpp)
GO(g_propagate_error, vFpp)
GO(g_propagate_prefixed_error, vFpppppppppppp)  //vaarg, should align?
GO(g_ptr_array_add, vFpp)
GOM(g_ptr_array_foreach, vFEppp)
GO(g_ptr_array_free, pFpi)
GO(g_ptr_array_insert, vFpip)
GO(g_ptr_array_new, pFv)
GOM(g_ptr_array_new_full, pFEup)
GOM(g_ptr_array_new_with_free_func, pFEp)
GO(g_ptr_array_ref, pFp)
GO(g_ptr_array_remove, vFpp)
GO(g_ptr_array_remove_fast, iFpp)
GO(g_ptr_array_remove_index, pFpu)
GO(g_ptr_array_remove_index_fast, pFpu)
GO(g_ptr_array_remove_range, pFpuu)
GOM(g_ptr_array_set_free_func, vFEpp)
GO(g_ptr_array_set_size, vFpi)
GO(g_ptr_array_sized_new, pFu)
GOM(g_ptr_array_sort, vFEpp)
GOM(g_ptr_array_sort_with_data, vFEppp)
GO(g_ptr_array_unref, vFp)
GOM(g_qsort_with_data, vFEpiLpp)
GO(g_quark_from_static_string, uFp)
GO(g_quark_from_string, uFp)
GO(g_quark_to_string, pFu)
GO(g_quark_try_string, uFp)
//GO(g_queue_clear, 
//GO(g_queue_copy, 
//GO(g_queue_delete_link, 
//GO(g_queue_find, 
//GO(g_queue_find_custom, 
//GO(g_queue_foreach, 
//GO(g_queue_free, 
//GO(g_queue_free_full, 
//GO(g_queue_get_length, 
//GO(g_queue_index, 
//GO(g_queue_init, 
//GO(g_queue_insert_after, 
//GO(g_queue_insert_before, 
//GO(g_queue_insert_sorted, 
//GO(g_queue_is_empty, 
//GO(g_queue_link_index, 
//GO(g_queue_new, 
//GO(g_queue_peek_head, 
//GO(g_queue_peek_head_link, 
//GO(g_queue_peek_nth, 
//GO(g_queue_peek_nth_link, 
//GO(g_queue_peek_tail, 
//GO(g_queue_peek_tail_link, 
//GO(g_queue_pop_head, 
//GO(g_queue_pop_head_link, 
//GO(g_queue_pop_nth, 
//GO(g_queue_pop_nth_link, 
//GO(g_queue_pop_tail, 
//GO(g_queue_pop_tail_link, 
//GO(g_queue_push_head, 
//GO(g_queue_push_head_link, 
//GO(g_queue_push_nth, 
//GO(g_queue_push_nth_link, 
//GO(g_queue_push_tail, 
//GO(g_queue_push_tail_link, 
//GO(g_queue_remove, 
//GO(g_queue_remove_all, 
//GO(g_queue_reverse, 
//GO(g_queue_sort, 
//GO(g_queue_unlink, 
//GO(g_rand_copy, 
//GO(g_rand_double, 
//GO(g_rand_double_range, 
//GO(g_rand_free, 
//GO(g_rand_int, 
//GO(g_rand_int_range, 
//GO(g_rand_new, 
//GO(g_rand_new_with_seed, 
//GO(g_rand_new_with_seed_array, 
//GO(g_random_double, 
//GO(g_random_double_range, 
//GO(g_random_int, 
//GO(g_random_int_range, 
//GO(g_random_set_seed, 
//GO(g_rand_set_seed, 
//GO(g_rand_set_seed_array, 
GO(g_realloc, pFpL)
GO(g_realloc_n, pFpLL)
//GO(g_rec_mutex_clear, 
//GO(g_rec_mutex_init, 
//GO(g_rec_mutex_lock, 
//GO(g_rec_mutex_trylock, 
//GO(g_rec_mutex_unlock, 
//GO(g_regex_check_replacement, 
//GO(g_regex_error_quark, 
//GO(g_regex_escape_nul, 
//GO(g_regex_escape_string, 
//GO(g_regex_get_capture_count, 
//GO(g_regex_get_compile_flags, 
//GO(g_regex_get_has_cr_or_lf, 
//GO(g_regex_get_match_flags, 
//GO(g_regex_get_max_backref, 
//GO(g_regex_get_max_lookbehind, 
//GO(g_regex_get_pattern, 
//GO(g_regex_get_string_number, 
//GO(g_regex_match, 
//GO(g_regex_match_all, 
//GO(g_regex_match_all_full, 
//GO(g_regex_match_full, 
//GO(g_regex_match_simple, 
//GO(g_regex_new, 
//GO(g_regex_ref, 
//GO(g_regex_replace, 
//GO(g_regex_replace_eval, 
//GO(g_regex_replace_literal, 
//GO(g_regex_split, 
//GO(g_regex_split_full, 
//GO(g_regex_split_simple, 
//GO(g_regex_unref, 
//GO(g_relation_count, 
//GO(g_relation_delete, 
//GO(g_relation_destroy, 
//GO(g_relation_exists, 
//GO(g_relation_index, 
//GO(g_relation_insert, 
//GO(g_relation_new, 
//GO(g_relation_print, 
//GO(g_relation_select, 
//GO(g_reload_user_special_dirs_cache, 
GO(g_remove, iFp)
GO(g_rename, iFpp)
GO(g_return_if_fail_warning, vFppp)
GO(g_rmdir, iFp)
//GO(g_rw_lock_clear, 
//GO(g_rw_lock_init, 
//GO(g_rw_lock_reader_lock, 
//GO(g_rw_lock_reader_trylock, 
//GO(g_rw_lock_reader_unlock, 
//GO(g_rw_lock_writer_lock, 
//GO(g_rw_lock_writer_trylock, 
//GO(g_rw_lock_writer_unlock, 
//GO(g_scanner_cur_line, 
//GO(g_scanner_cur_position, 
//GO(g_scanner_cur_token, 
//GO(g_scanner_cur_value, 
//GO(g_scanner_destroy, 
//GO(g_scanner_eof, 
//GO(g_scanner_error, 
//GO(g_scanner_get_next_token, 
//GO(g_scanner_input_file, 
//GO(g_scanner_input_text, 
//GO(g_scanner_lookup_symbol, 
//GO(g_scanner_new, 
//GO(g_scanner_peek_next_token, 
//GO(g_scanner_scope_add_symbol, 
//GO(g_scanner_scope_foreach_symbol, 
//GO(g_scanner_scope_lookup_symbol, 
//GO(g_scanner_scope_remove_symbol, 
//GO(g_scanner_set_scope, 
//GO(g_scanner_sync_file_offset, 
//GO(g_scanner_unexp_token, 
//GO(g_scanner_warn, 
//GO(g_sequence_append, 
//GO(g_sequence_foreach, 
//GO(g_sequence_foreach_range, 
//GO(g_sequence_free, 
//GO(g_sequence_get, 
//GO(g_sequence_get_begin_iter, 
//GO(g_sequence_get_end_iter, 
//GO(g_sequence_get_iter_at_pos, 
//GO(g_sequence_get_length, 
//GO(g_sequence_insert_before, 
//GO(g_sequence_insert_sorted, 
//GO(g_sequence_insert_sorted_iter, 
//GO(g_sequence_iter_compare, 
//GO(g_sequence_iter_get_position, 
//GO(g_sequence_iter_get_sequence, 
//GO(g_sequence_iter_is_begin, 
//GO(g_sequence_iter_is_end, 
//GO(g_sequence_iter_move, 
//GO(g_sequence_iter_next, 
//GO(g_sequence_iter_prev, 
//GO(g_sequence_lookup, 
//GO(g_sequence_lookup_iter, 
//GO(g_sequence_move, 
//GO(g_sequence_move_range, 
//GO(g_sequence_new, 
//GO(g_sequence_prepend, 
//GO(g_sequence_range_get_midpoint, 
//GO(g_sequence_remove, 
//GO(g_sequence_remove_range, 
//GO(g_sequence_search, 
//GO(g_sequence_search_iter, 
//GO(g_sequence_set, 
//GO(g_sequence_sort, 
//GO(g_sequence_sort_changed, 
//GO(g_sequence_sort_changed_iter, 
//GO(g_sequence_sort_iter, 
//GO(g_sequence_swap, 
GO(g_set_application_name, vFp)
GO(g_setenv, iFppi)
GO(g_set_error, vFppipppppppppp)    // vaarg, and no valist equivalent it seems. Should wrap with literal version probably
GO(g_set_error_literal, vFppip)
GO(g_set_prgname, vFp)
//GOM(g_set_printerr_handler, BFEB)
//GOM(g_set_print_handler, BFEB)
//GO(g_shell_error_quark, 
GO(g_shell_parse_argv, iFpppp)
GO(g_shell_quote, pFp)
GO(g_shell_unquote, pFpp)
GO(g_slice_alloc, pFL)
GO(g_slice_alloc0, pFL)
GO(g_slice_copy, pFLp)
GO(g_slice_free1, vFLp)
GO(g_slice_free_chain_with_offset, vFLpL)
GO(g_slice_get_config, IFi)
GO(g_slice_get_config_state, pFiIp)
GO(g_slice_set_config, vFiI)
GO(g_slist_alloc, pFv)
GO(g_slist_append, pFpp)
GO(g_slist_concat, pFpp)
GO(g_slist_copy, pFp)
//GOM(g_slist_copy_deep, pFEppp)
GO(g_slist_delete_link, pFpp)
GO(g_slist_find, pFpp)
GOM(g_slist_find_custom, pFEppp)
GOM(g_slist_foreach, pFEppp)
GO(g_slist_free, vFp)
GO(g_slist_free_1, vFp)
//GOM(g_slist_free_full, vFEpp)
GO(g_slist_index, iFpp)
GO(g_slist_insert, pFppi)
GO(g_slist_insert_before, pFppp)
GOM(g_slist_insert_sorted, pFEppp)
GOM(g_slist_insert_sorted_with_data, pFEpppp)
GO(g_slist_last, pFp)
GO(g_slist_length, uFp)
GO(g_slist_nth, pFpu)
GO(g_slist_nth_data, pFpu)
//GO(g_slist_pop_allocator, 
GO(g_slist_position, iFpp)
GO(g_slist_prepend, pFpp)
//GO(g_slist_push_allocator, 
GO(g_slist_remove, pFpp)
GO(g_slist_remove_all, pFpp)
GO(g_slist_remove_link, pFpp)
GO(g_slist_reverse, pFp)
//GOM(g_slist_sort, pFEpp)
//GOM(g_slist_sort_with_data, pFEppp)
GO2(g_snprintf, iFEpLpV, my_g_vsnprintf)
GO(g_source_add_child_source, vFpp)
GO(g_source_add_poll, vFpp)
GO(g_source_add_unix_fd, pFpii)
GO(g_source_attach, uFpp)
GO(g_source_destroy, vFp)
GO(g_source_get_can_recurse, iFp)
GO(g_source_get_context, pFp)
GO(g_source_get_current_time, vFpp)
GO(g_source_get_id, uFp)
GO(g_source_get_name, pFp)
GO(g_source_get_priority, iFp)
GO(g_source_get_ready_time, IFp)
GO(g_source_get_time, IFp)
GO(g_source_is_destroyed, iFp)
GO(g_source_modify_unix_fd, vFppi)
GOM(g_source_new, pFEpu)
GO(g_source_query_unix_fd, iFpp)
GO(g_source_ref, pFp)
GO(g_source_remove, iFu)
GOM(g_source_remove_by_funcs_user_data, iFEpp)
GO(g_source_remove_by_user_data, iFp)
GO(g_source_remove_child_source, vFpp)
GO(g_source_remove_poll, vFpp)
GO(g_source_remove_unix_fd, vFpp)
GOM(g_source_set_callback, vFEpppp)
//GOM(g_source_set_callback_indirect, vFEppB)
GO(g_source_set_can_recurse, vFpi)
GOM(g_source_set_funcs, vFEpp)
GO(g_source_set_name, vFpp)
GO(g_source_set_name_by_id, vFup)
GO(g_source_set_priority, vFpi)
GO(g_source_set_ready_time, vFpI)
GO(g_source_unref, vFp)
GO(g_spaced_primes_closest, uFu)
GOM(g_spawn_async, iFEpppipppp)
GOM(g_spawn_async_with_pipes, iFEpppippppppp)
GO(g_spawn_check_exit_status, iFip)
GO(g_spawn_close_pid, vFp)
GO(g_spawn_command_line_async, iFpp)
GO(g_spawn_command_line_sync, iFppppp)
GO(g_spawn_error_quark, pFv)
GO(g_spawn_exit_error_quark, pFv)
GOM(g_spawn_sync, iFEpppipppppp)
GO2(g_sprintf, iFEppV, my_g_vsprintf)
GO(g_stat, iFpp)
GO(g_static_mutex_free, vFp)
GO(g_static_mutex_get_mutex_impl, pFp)
GO(g_static_mutex_init, vFp)
GO(g_static_private_free, vFp)
GO(g_static_private_get, pFp)
GO(g_static_private_init, vFp)
GOM(g_static_private_set, vFEppp)
GO(g_static_rec_mutex_free, vFp)
GO(g_static_rec_mutex_init, vFp)
GO(g_static_rec_mutex_lock, vFp)
GO(g_static_rec_mutex_lock_full, vFpu)
GO(g_static_rec_mutex_trylock, iFp)
GO(g_static_rec_mutex_unlock, vFp)
GO(g_static_rec_mutex_unlock_full, uFp)
GO(g_static_rw_lock_free, vFp)
GO(g_static_rw_lock_init, vFp)
GO(g_static_rw_lock_reader_lock, vFp)
GO(g_static_rw_lock_reader_trylock, iFp)
GO(g_static_rw_lock_reader_unlock, vFp)
GO(g_static_rw_lock_writer_lock, vFp)
GO(g_static_rw_lock_writer_trylock, iFp)
GO(g_static_rw_lock_writer_unlock, vFp)
GO(g_stpcpy, pFpp)
GO(g_strcanon, pFppC)
GO(g_strcasecmp, iFpp)
GO(g_strchomp, pFp)
GO(g_strchug, pFp)
GO(g_strcmp0, iFpp)
GO(g_strcompress, pFp)
GO(g_strconcat, pFppppppppppppp)    //vaarg, no va_list equivalent...
GO(g_strdelimit, pFppC)
GO(g_strdown, pFp)
GO(g_strdup, pFp)
GO2(g_strdup_printf, pFEpV, my_g_strdup_vprintf)
GO(g_strdupv, pFp)
GOM(g_strdup_vprintf, pFEpp)
GO(g_str_equal, iFpp)
GO(g_strerror, pFi)
GO(g_strescape, pFpp)
GO(g_strfreev, vFp)
GO(g_str_hash, uFp)
GO(g_str_has_prefix, iFpp)
GO(g_str_has_suffix, iFpp)
GO(g_string_append, pFpp)
GO(g_string_append_c, pFpC)
GO(g_string_append_len, pFppl)
GO2(g_string_append_printf, vFppV, g_string_append_vprintf) // need align?
GO(g_string_append_unichar, pFpu)
GO(g_string_append_uri_escaped, pFpppi)
GO(g_string_append_vprintf, vFppp)
GO(g_string_ascii_down, pFp)
GO(g_string_ascii_up, pFp)
GO(g_string_assign, pFpp)
GO(g_string_chunk_clear, vFp)
GO(g_string_chunk_free, vFp)
GO(g_string_chunk_insert, pFpp)
GO(g_string_chunk_insert_const, pFpp)
GO(g_string_chunk_insert_len, pFppl)
GO(g_string_chunk_new, pFL)
GO(g_string_down, pFp)
GO(g_string_equal, iFpp)
GO(g_string_erase, pFpll)
GO(g_string_free, pFpi)
GO(g_string_free_to_bytes, pFp)
GO(g_string_hash, uFp)
GO(g_string_insert, pFplp)
GO(g_string_insert_c, pFplC)
GO(g_string_insert_len, pFplpl)
GO(g_string_insert_unichar, pFplu)
GO(g_string_new, pFp)
GO(g_string_new_len, pFpl)
GO(g_string_overwrite, pFplp)
GO(g_string_overwrite_len, pFplpl)
GO(g_string_prepend, pFpp)
GO(g_string_prepend_c, pFpC)
GO(g_string_prepend_len, pFppl)
GO(g_string_prepend_unichar, pFpu)
GO2(g_string_printf, vFppV, g_string_vprintf)   // need align?
GO(g_string_set_size, pFpL)
GO(g_string_sized_new, pFL)
GO(g_string_truncate, pFpL)
GO(g_string_up, pFp)
GO(g_string_vprintf, vFppp)
GO(g_strip_context, pFpp)
GO(g_str_is_ascii, iFp)
GO2(g_strjoin, pFpV, g_strjoinv)
GO(g_strjoinv, pFpp)    // no need to align, ony string pointers here
GO(g_strlcat, uFppu)
GO(g_strlcpy, uFppu)
GO(g_str_match_string, iFppi)
GO(g_strncasecmp, iFppu)
GO(g_strndup, pFpu)
GO(g_strnfill, pFuC)
GO(g_strreverse, pFp)
GO(g_strrstr, pFpp)
GO(g_strrstr_len, pFpip)
GO(g_strsignal, pFi)
GO(g_strsplit, pFppi)
GO(g_strsplit_set, pFppi)
GO(g_strstr_len, pFpip)
GO(g_str_to_ascii, pFpp)
GO(g_strtod, dFpp)
GO(g_str_tokenize_and_fold, pFppp)
GO(g_strup, pFp)
GO(g_strv_length, uFp)
//GO(g_test_add_data_func, 
//GO(g_test_add_data_func_full, 
//GO(g_test_add_func, 
//GO(g_test_add_vtable, 
//GO(g_test_assert_expected_messages_internal, 
//GO(g_test_bug, 
//GO(g_test_bug_base, 
//GO(g_test_build_filename, 
//GO(g_test_create_case, 
//GO(g_test_create_suite, 
//GO(g_test_expect_message, 
//GO(g_test_fail, 
//GO(g_test_failed, 
//GO(g_test_get_dir, 
//GO(g_test_get_filename, 
//GO(g_test_get_root, 
//GO(g_test_incomplete, 
//GO(g_test_init, 
//GO(g_test_log_buffer_free, 
//GO(g_test_log_buffer_new, 
//GO(g_test_log_buffer_pop, 
//GO(g_test_log_buffer_push, 
//GO(g_test_log_msg_free, 
//GO(g_test_log_set_fatal_handler, 
//GO(g_test_log_type_name, 
//GO(g_test_maximized_result, 
//GO(g_test_message, 
//GO(g_test_minimized_result, 
//GO(g_test_queue_destroy, 
//GO(g_test_queue_free, 
//GO(g_test_rand_double, 
//GO(g_test_rand_double_range, 
//GO(g_test_rand_int, 
//GO(g_test_rand_int_range, 
//GO(g_test_run, 
//GO(g_test_run_suite, 
//GO(g_test_set_nonfatal_assertions, 
//GO(g_test_skip, 
//GO(g_test_subprocess, 
//GO(g_test_suite_add, 
//GO(g_test_suite_add_suite, 
//GO(g_test_timer_elapsed, 
//GO(g_test_timer_last, 
//GO(g_test_timer_start, 
//GO(g_test_trap_assertions, 
//GO(g_test_trap_fork, 
//GO(g_test_trap_has_passed, 
//GO(g_test_trap_reached_timeout, 
//GO(g_test_trap_subprocess, 
GOM(g_thread_create, pFEppip)
GOM(g_thread_create_full, pFEppLiiip)
//GO(g_thread_error_quark, 
GO(g_thread_exit, vFp)
GOM(g_thread_foreach, vFEpp)
//GO(g_thread_get_initialized, 
//GO(g_thread_init_glib, 
GO(g_thread_join, pFp)
//GO(g_thread_new, 
//GO(g_thread_pool_free, 
//GO(g_thread_pool_get_max_idle_time, 
//GO(g_thread_pool_get_max_threads, 
//GO(g_thread_pool_get_max_unused_threads, 
//GO(g_thread_pool_get_num_threads, 
//GO(g_thread_pool_get_num_unused_threads, 
//GO(g_thread_pool_new, 
//GO(g_thread_pool_push, 
//GO(g_thread_pool_set_max_idle_time, 
//GO(g_thread_pool_set_max_threads, 
//GO(g_thread_pool_set_max_unused_threads, 
//GO(g_thread_pool_set_sort_function, 
//GO(g_thread_pool_stop_unused_threads, 
//GO(g_thread_pool_unprocessed, 
GO(g_thread_ref, pFp)
GO(g_thread_self, pFv)
GO(g_thread_set_priority, vFpi)
//GO(g_thread_try_new, 
GO(g_thread_unref, vFp)
GO(g_thread_yield, vFv)
GOM(g_timeout_add, uFEupp)
//GOM(g_timeout_add_full, uFEiuBpB)
//GOM(g_timeout_add_seconds, uFEuBp)
//GOM(g_timeout_add_seconds_full, uFEiuBpB)
GO(g_timeout_source_new, pFu)
GO(g_timeout_source_new_seconds, pFu)
//GO(g_timer_continue, 
//GO(g_timer_destroy, 
//GO(g_timer_elapsed, 
//GO(g_timer_new, 
//GO(g_timer_reset, 
//GO(g_timer_start, 
//GO(g_timer_stop, 
GO(g_time_val_add, vFpl)
GO(g_time_val_from_iso8601, iFpp)
GO(g_time_val_to_iso8601, pFp)
//GO(g_time_zone_adjust_time, 
//GO(g_time_zone_find_interval, 
//GO(g_time_zone_get_abbreviation, 
//GO(g_time_zone_get_offset, 
//GO(g_time_zone_is_dst, 
//GO(g_time_zone_new, 
//GO(g_time_zone_new_local, 
//GO(g_time_zone_new_utc, 
//GO(g_time_zone_ref, 
//GO(g_time_zone_unref, 
//GO(g_trash_stack_height, 
//GO(g_trash_stack_peek, 
//GO(g_trash_stack_pop, 
//GO(g_trash_stack_push, 
//GO(g_tree_destroy, 
//GO(g_tree_foreach, 
//GO(g_tree_height, 
//GO(g_tree_insert, 
//GO(g_tree_lookup, 
//GO(g_tree_lookup_extended, 
//GO(g_tree_new, 
//GO(g_tree_new_full, 
//GO(g_tree_new_with_data, 
//GO(g_tree_nnodes, 
//GO(g_tree_ref, 
//GO(g_tree_remove, 
//GO(g_tree_replace, 
//GO(g_tree_search, 
//GO(g_tree_steal, 
//GO(g_tree_traverse, 
//GO(g_tree_unref, 
GO(g_try_malloc, pFL)
GO(g_try_malloc0, pFL)
GO(g_try_malloc0_n, pFLL)
GO(g_try_malloc_n, pFLL)
GO(g_try_realloc, pFpL)
GO(g_try_realloc_n, pFpLL)
//GO(g_tuples_destroy, 
//GO(g_tuples_index, 
GO(g_ucs4_to_utf16, pFplppp)
GO(g_ucs4_to_utf8, pFplppp)
GO(g_unichar_break_type, iFu)
GO(g_unichar_combining_class, iFu)
GO(g_unichar_compose, iFuup)
GO(g_unichar_decompose, iFupp)
GO(g_unichar_digit_value, iFu)
GO(g_unichar_fully_decompose, iFuipu)
GO(g_unichar_get_mirror_char, iFup)
GO(g_unichar_get_script, iFu)
GO(g_unichar_isalnum, iFu)
GO(g_unichar_isalpha, iFu)
GO(g_unichar_iscntrl, iFu)
GO(g_unichar_isdefined, iFu)
GO(g_unichar_isdigit, iFu)
GO(g_unichar_isgraph, iFu)
GO(g_unichar_islower, iFu)
GO(g_unichar_ismark, iFu)
GO(g_unichar_isprint, iFu)
GO(g_unichar_ispunct, iFu)
GO(g_unichar_isspace, iFu)
GO(g_unichar_istitle, iFu)
GO(g_unichar_isupper, iFu)
GO(g_unichar_iswide, iFu)
GO(g_unichar_iswide_cjk, iFu)
GO(g_unichar_isxdigit, iFu)
GO(g_unichar_iszerowidth, iFu)
GO(g_unichar_tolower, uFu)
GO(g_unichar_totitle, uFu)
GO(g_unichar_toupper, uFu)
GO(g_unichar_to_utf8, iFup)
GO(g_unichar_type, iFu)
GO(g_unichar_validate, iFu)
GO(g_unichar_xdigit_value, iFu)
GO(g_unicode_canonical_decomposition, pFup)
GO(g_unicode_canonical_ordering, vFpu)
GO(g_unicode_script_from_iso15924, iFu)
GO(g_unicode_script_to_iso15924, uFi)
//GO(g_unix_error_quark, 
//GO(g_unix_fd_add, 
//GO(g_unix_fd_add_full, 
//GO(g_unix_fd_source_new, 
//GO(g_unix_open_pipe, 
//GO(g_unix_set_fd_nonblocking, 
//GO(g_unix_signal_add, 
//GO(g_unix_signal_add_full, 
//GO(g_unix_signal_source_new, 
GO(g_unlink, iFp)
GO(g_unsetenv, vFp)
GO(g_uri_escape_string, pFppi)
GO(g_uri_list_extract_uris, pFp)
GO(g_uri_parse_scheme, pFp)
GO(g_uri_unescape_segment, pFppp)
GO(g_uri_unescape_string, pFpp)
GO(g_usleep, vFL)
GO(g_utf16_to_ucs4, pFplppp)
GO(g_utf16_to_utf8, pFplppp)
GO(g_utf8_casefold, pFpi)
GO(g_utf8_collate, iFpp)
GO(g_utf8_collate_key, pFpi)
GO(g_utf8_collate_key_for_filename, pFpi)
GO(g_utf8_find_next_char, pFpp)
GO(g_utf8_find_prev_char, pFpp)
GO(g_utf8_get_char, uFp)
GO(g_utf8_get_char_validated, uFpi)
GO(g_utf8_normalize, pFpii)
GO(g_utf8_offset_to_pointer, pFpl)
GO(g_utf8_pointer_to_offset, lFpp)
GO(g_utf8_prev_char, pFp)
GO(g_utf8_strchr, pFpiu)
GO(g_utf8_strdown, pFpi)
GO(g_utf8_strlen, lFpi)
GO(g_utf8_strncpy, pFppu)
GO(g_utf8_strrchr, pFpiu)
GO(g_utf8_strreverse, pFpi)
GO(g_utf8_strup, pFpi)
GO(g_utf8_substring, pFpll)
GO(g_utf8_to_ucs4, pFplppp)
GO(g_utf8_to_ucs4_fast, pFplp)
GO(g_utf8_to_utf16, pFplppp)
GO(g_utf8_validate, iFplp)
GO(g_utime, iFpp)
GO(g_variant_builder_add, vFppppppppppp)    // vaarg
GO(g_variant_builder_add_parsed, vFppppppppppp) //vaarg
GO(g_variant_builder_add_value, vFpp)
GO(g_variant_builder_clear, vFp)
GO(g_variant_builder_close, vFp)
GO(g_variant_builder_end, pFp)
GO(g_variant_builder_init, vFpp)
GO(g_variant_builder_new, pFp)
GO(g_variant_builder_open, vFpp)
GO(g_variant_builder_ref, pFp)
GO(g_variant_builder_unref, vFp)
GO(g_variant_byteswap, pFp)
GO(g_variant_check_format_string, iFppi)
GO(g_variant_classify, iFp)
GO(g_variant_compare, iFpp)
GO(g_variant_dict_clear, vFp)
GO(g_variant_dict_contains, iFpp)
GO(g_variant_dict_end, pFp)
GO(g_variant_dict_init, vFpp)
GO(g_variant_dict_insert, vFpppppppppppppp) //vaarg
GO(g_variant_dict_insert_value, vFppp)
GO(g_variant_dict_lookup, iFppppppppppppp)  //vaarg
GO(g_variant_dict_lookup_value, pFppp)
GO(g_variant_dict_new, pFp)
GO(g_variant_dict_ref, pFp)
GO(g_variant_dict_remove, iFpp)
GO(g_variant_dict_unref, vFp)
GO(g_variant_dup_bytestring, pFpp)
GO(g_variant_dup_bytestring_array, pFpp)
GO(g_variant_dup_objv, pFpp)
GO(g_variant_dup_string, pFpp)
GO(g_variant_dup_strv, pFpp)
GO(g_variant_equal, iFpp)
//GO(g_variant_format_string_scan, 
//GO(g_variant_format_string_scan_type, 
GOM(g_variant_get, vFEppV)
GO(g_variant_get_boolean, iFp)
GO(g_variant_get_byte, CFp)
GO(g_variant_get_bytestring, pFp)
GO(g_variant_get_bytestring_array, pFpp)
GO(g_variant_get_child, vFpuppppppppppp)    //vaarg here
GO(g_variant_get_child_value, pFpu)
GO(g_variant_get_data, pFp)
GO(g_variant_get_data_as_bytes, pFp)
GO(g_variant_get_double, dFp)
GO(g_variant_get_fixed_array, pFppu)
GO(g_variant_get_handle, iFp)
GO(g_variant_get_int16, wFp)
GO(g_variant_get_int32, iFp)
GO(g_variant_get_int64, IFp)
GO(g_variant_get_maybe, pFp)
GO(g_variant_get_normal_form, pFp)
GO(g_variant_get_objv, pFpp)
GO(g_variant_get_size, uFp)
GO(g_variant_get_string, pFpp)
GO(g_variant_get_strv, pFpp)
GO(g_variant_get_type, pFp)
GO(g_variant_get_type_string, pFp)
GO(g_variant_get_uint16, WFp)
GO(g_variant_get_uint32, uFp)
GO(g_variant_get_uint64, UFp)
GO(g_variant_get_va, vFpppp)
GO(g_variant_get_variant, pFp)
GO(g_variant_hash, uFp)
GO(g_variant_is_container, iFp)
GO(g_variant_is_floating, iFp)
GO(g_variant_is_normal_form, iFp)
GO(g_variant_is_object_path, iFp)
GO(g_variant_is_of_type, iFpp)
GO(g_variant_is_signature, iFp)
GO(g_variant_iter_copy, pFp)
GO(g_variant_iter_free, vFp)
GO(g_variant_iter_init, uFpp)
GO(g_variant_iter_loop, iFpppppppppppp) // vaarg
GO(g_variant_iter_n_children, uFp)
GO(g_variant_iter_new, pFp)
GO(g_variant_iter_next, iFpppppppppppp) // vaarg here
GO(g_variant_iter_next_value, pFp)
GO(g_variant_lookup, iFpppppppppppp)    // vaarg
GO(g_variant_lookup_value, pFppp)
GO(g_variant_n_children, uFp)
GOM(g_variant_new, pFEpV)
GO(g_variant_new_array, pFppu)
GO(g_variant_new_boolean, pFi)
GO(g_variant_new_byte, pFC)
GO(g_variant_new_bytestring, pFp)
GO(g_variant_new_bytestring_array, pFpi)
GO(g_variant_new_dict_entry, pFpp)
GO(g_variant_new_double, pFd)
GO(g_variant_new_fixed_array, pFppuu)
GO(g_variant_new_from_bytes, pFppi)
GOM(g_variant_new_from_data, pFEppuipp)
GO(g_variant_new_handle, pFi)
GO(g_variant_new_int16, pFw)
GO(g_variant_new_int32, pFi)
GO(g_variant_new_int64, pFI)
GO(g_variant_new_maybe, pFpp)
GO(g_variant_new_object_path, pFp)
GO(g_variant_new_objv, pFpi)
GO2(g_variant_new_parsed, pFEpV, my_g_variant_new_parsed_va)
GOM(g_variant_new_parsed_va, pFEpp)
//GO(g_variant_new_printf,  // needs alignment.....
GO(g_variant_new_signature, pFp)
GO(g_variant_new_string, pFp)
GO(g_variant_new_strv, pFpi)
GO(g_variant_new_take_string, pFp)
GO(g_variant_new_tuple, pFpu)
GO(g_variant_new_uint16, pFW)
GO(g_variant_new_uint32, pFu)
GO(g_variant_new_uint64, pFU)
GO(g_variant_new_va, pFppp)
GO(g_variant_new_variant, pFp)
GO(g_variant_parse, pFppppp)
GO(g_variant_parse_error_print_context, pFpp)
//GO(g_variant_parse_error_quark, 
//GO(g_variant_parser_get_error_quark, 
GO(g_variant_print, pFpi)
GO(g_variant_print_string, pFppi)
GO(g_variant_ref, pFp)
GO(g_variant_ref_sink, pFp)
//GO(g_variant_serialised_byteswap, 
//GO(g_variant_serialised_get_child, 
//GO(g_variant_serialised_is_normal, 
//GO(g_variant_serialised_n_children, 
//GO(g_variant_serialiser_is_object_path, 
//GO(g_variant_serialiser_is_signature, 
//GO(g_variant_serialiser_is_string, 
//GO(g_variant_serialiser_needed_size, 
//GO(g_variant_serialiser_serialise, 
GO(g_variant_store, vFp)
GO(g_variant_take_ref, pFp)
GO(g_variant_type_checked_, pFp)
//GO(g_variant_type_copy, 
//GO(g_variant_type_dup_string, 
//GO(g_variant_type_element, 
//GO(g_variant_type_equal, 
//GO(g_variant_type_first, 
//GO(g_variant_type_free, 
//GO(g_variant_type_get_string_length, 
//GO(g_variant_type_hash, 
//GO(g_variant_type_info_assert_no_infos, 
//GO(g_variant_type_info_element, 
//GO(g_variant_type_info_get, 
//GO(g_variant_type_info_get_type_string, 
//GO(g_variant_type_info_member_info, 
//GO(g_variant_type_info_n_members, 
//GO(g_variant_type_info_query, 
//GO(g_variant_type_info_query_element, 
//GO(g_variant_type_info_ref, 
//GO(g_variant_type_info_unref, 
//GO(g_variant_type_is_array, 
//GO(g_variant_type_is_basic, 
//GO(g_variant_type_is_container, 
//GO(g_variant_type_is_definite, 
//GO(g_variant_type_is_dict_entry, 
//GO(g_variant_type_is_maybe, 
//GO(g_variant_type_is_subtype_of, 
//GO(g_variant_type_is_tuple, 
//GO(g_variant_type_is_variant, 
//GO(g_variant_type_key, 
//GO(g_variant_type_new, 
//GO(g_variant_type_new_array, 
//GO(g_variant_type_new_dict_entry, 
//GO(g_variant_type_new_maybe, 
//GO(g_variant_type_new_tuple, 
//GO(g_variant_type_next, 
//GO(g_variant_type_n_items, 
//GO(g_variant_type_peek_string, 
//GO(g_variant_type_string_is_valid, 
//GO(g_variant_type_string_scan, 
//GO(g_variant_type_value, 
GO(g_variant_unref, vFp)
GOM(g_vasprintf, iFEppp)
GOM(g_vfprintf, iFEppp)
GOM(g_vprintf, iFEpp)
GOM(g_vsnprintf, iFEpLpp)
GOM(g_vsprintf, iFEppp)
GO(g_warn_message, vFppipp)
//GO(_init, 

DATA(g_ascii_table, 4)
//GLOB(g_threads_got_initialized, 4)