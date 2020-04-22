#if !(defined(GO) && defined(GOM) && defined(GO2) && defined(DATA))
#error Meh....
#endif

GO(dbus_address_entries_free, vFp)
GO(dbus_address_entry_get_method, pFp)
GO(dbus_address_entry_get_value, pFpp)
GO(dbus_address_escape_value, pFp)
GO(dbus_address_unescape_value, pFpp)
GO(dbus_bus_add_match, vFpp)
GO(dbus_bus_get, pFip)
GO(dbus_bus_get_id, pFpp)
GO(dbus_bus_get_private, pFip)
GO(dbus_bus_get_unique_name, pFp)
GO(dbus_bus_get_unix_user, uFppp)
GO(dbus_bus_name_has_owner, iFppp)
GO(dbus_bus_register, iFpp)
GO(dbus_bus_release_name, iFppp)
GO(dbus_bus_remove_match, vFppp)
GO(dbus_bus_request_name, iFppup)
GO(dbus_bus_set_unique_name, iFpp)
GO(dbus_bus_start_service_by_name, iFppupp)
GOM(dbus_connection_add_filter, iFEpppp)
GO(dbus_connection_allocate_data_slot, iFp)
GO(dbus_connection_borrow_message, pFp)
GO(dbus_connection_close, vFp)
GO(dbus_connection_dispatch, iFp)
GO(dbus_connection_flush, vFp)
GO(dbus_connection_free_data_slot, vFp)
GO(dbus_connection_free_preallocated_send, vFpp)
GO(dbus_connection_get_adt_audit_session_data, iFppp)
GO(dbus_connection_get_data, pFpi)
GO(dbus_connection_get_dispatch_status, iFp)
GO(dbus_connection_get_is_anonymous, iFp)
GO(dbus_connection_get_is_authenticated, iFp)
GO(dbus_connection_get_is_connected, iFp)
GO(dbus_connection_get_max_message_size, lFp)
GO(dbus_connection_get_max_received_size, lFp)
GO(dbus_connection_get_object_path_data, iFppp)
GO(dbus_connection_get_outgoing_size, lFp)
GO(dbus_connection_get_server_id, pFp)
GO(dbus_connection_get_socket, iFpp)
GO(dbus_connection_get_unix_fd, iFpp)
GO(dbus_connection_get_unix_process_id, iFpp)
GO(dbus_connection_get_unix_user, iFpp)
GO(dbus_connection_get_windows_user, iFpp)
GO(dbus_connection_has_messages_to_send, iFp)
GO(dbus_connection_list_registered, iFppp)
GO(dbus_connection_open, pFpp)
GO(dbus_connection_open_private, pFpp)
GO(dbus_connection_pop_message, pFp)
GO(dbus_connection_preallocate_send, pFp)
GO(dbus_connection_read_write, iFpi)
GO(dbus_connection_read_write_dispatch, iFpi)
GO(dbus_connection_ref, pFp)
//GO(dbus_connection_register_fallback, 
//GO(dbus_connection_register_object_path, 
GOM(dbus_connection_remove_filter, vFEppp)
GO(dbus_connection_return_message, vFpp)
GO(dbus_connection_send, iFppp)
GO(dbus_connection_send_preallocated, vFpppp)
GO(dbus_connection_send_with_reply, iFppp)
GO(dbus_connection_send_with_reply_and_block, pFppip)
GO(dbus_connection_set_allow_anonymous, vFpi)
GO(dbus_connection_set_change_sigpipe, vFi)
//GO(dbus_connection_set_data, 
//GO(dbus_connection_set_dispatch_status_function, 
GO(dbus_connection_set_exit_on_disconnect, vFpi)
GO(dbus_connection_set_max_message_size, vFpl)
GO(dbus_connection_set_max_received_size, vFpl)
GO(dbus_connection_set_route_peer_messages, vFpi)
GOM(dbus_connection_set_timeout_functions, iFEpppppp)
//GO(dbus_connection_set_unix_user_function, 
//GO(dbus_connection_set_wakeup_main_function, 
//GO(dbus_connection_set_watch_functions, 
//GO(dbus_connection_set_windows_user_function, 
GO(dbus_connection_steal_borrowed_message, vFpp)
//GO(dbus_connection_try_register_fallback, 
//GO(dbus_connection_try_register_object_path, 
GO(dbus_connection_unref, vFp)
GO(dbus_connection_unregister_object_path, iFpp)
GO(dbus_error_free, vFp)
GO(dbus_error_has_name, iFpp)
GO(dbus_error_init, vFp)
GO(dbus_error_is_set, iFp)
//GO(dbus_free, 
//GO(dbus_free_string_array, 
//GO(dbus_get_local_machine_id, 
//GO(dbus_get_version, 
//GO(dbus_internal_do_not_use_create_uuid, 
//GO(dbus_internal_do_not_use_get_uuid, 
//GO(dbus_malloc, 
//GO(dbus_malloc0, 
GO(dbus_message_allocate_data_slot, iFp)
GO2(dbus_message_append_args, iFpiV, dbus_message_append_args_valist)
GO(dbus_message_append_args_valist, iFpip)
GO(dbus_message_copy, pFp)
GO(dbus_message_demarshal, pFpip)
GO(dbus_message_demarshal_bytes_needed, iFpi)
GO(dbus_message_free_data_slot, vFp)
GOM(dbus_message_get_args, iFEppiV)
GOM(dbus_message_get_args_valist, iFEppiV)
GO(dbus_message_get_auto_start, iFp)
GO(dbus_message_get_data, pFpi)
GO(dbus_message_get_destination, pFp)
GO(dbus_message_get_error_name, pFp)
GO(dbus_message_get_interface, pFp)
GO(dbus_message_get_member, pFp)
GO(dbus_message_get_no_reply, iFp)
GO(dbus_message_get_path, pFp)
GO(dbus_message_get_path_decomposed, iFpp)
GO(dbus_message_get_reply_serial, uFp)
GO(dbus_message_get_sender, pFp)
GO(dbus_message_get_serial, iFp)
GO(dbus_message_get_signature, pFp)
GO(dbus_message_get_type, iFp)
GO(dbus_message_has_destination, iFpp)
GO(dbus_message_has_interface, iFpp)
GO(dbus_message_has_member, iFpp)
GO(dbus_message_has_path, iFpp)
GO(dbus_message_has_sender, iFpp)
GO(dbus_message_has_signature, iFpp)
GO(dbus_message_is_error, iFpp)
GO(dbus_message_is_method_call, iFppp)
GO(dbus_message_is_signal, iFppp)
GO(dbus_message_iter_abandon_container, vFpp)
GO(dbus_message_iter_append_basic, iFpip)
GO(dbus_message_iter_append_fixed_array, iFpipi)
GO(dbus_message_iter_close_container, iFpp)
GO(dbus_message_iter_get_arg_type, iFp)
GO(dbus_message_iter_get_array_len, iFp)
GO(dbus_message_iter_get_basic, vFpp)
GO(dbus_message_iter_get_element_type, iFp)
GO(dbus_message_iter_get_fixed_array, vFppp)
GO(dbus_message_iter_get_signature, pFp)
GO(dbus_message_iter_has_next, iFp)
GO(dbus_message_iter_init, iFpp)
GO(dbus_message_iter_init_append, vFpp)
GO(dbus_message_iter_next, iFp)
GO(dbus_message_iter_open_container, iFpipp)
GO(dbus_message_iter_recurse, vFpp)
GO(dbus_message_lock, vFp)
GO(dbus_message_marshal, iFppp)
GO(dbus_message_new, pFi)
GO(dbus_message_new_error, pFppp)
GO(dbus_message_new_error_printf, pFpppppppppppp)   //vaarg, should wrap and use vaprintf...
GO(dbus_message_new_method_call, pFpppp)
GO(dbus_message_new_method_return, pFp)
GO(dbus_message_new_signal, pFppp)
GO(dbus_message_ref, pFp)
GO(dbus_message_set_auto_start, vFpi)
GOM(dbus_message_set_data, iFEpipp)
GO(dbus_message_set_destination, iFpp)
GO(dbus_message_set_error_name, iFpp)
GO(dbus_message_set_interface, iFpp)
GO(dbus_message_set_member, iFpp)
GO(dbus_message_set_no_reply, vFpi)
GO(dbus_message_set_path, iFpp)
GO(dbus_message_set_reply_serial, iFpu)
GO(dbus_message_set_sender, iFpp)
GO(dbus_message_set_serial, vFpu)
GO(dbus_message_type_from_string, iFp)
GO(dbus_message_type_to_string, pFi)
GO(dbus_message_unref, vFp)
GO(dbus_move_error, vFpp)
GO(dbus_parse_address, iFpppp)
GO(dbus_pending_call_allocate_data_slot, iFp)
GO(dbus_pending_call_block, vFp)
GO(dbus_pending_call_cancel, vFp)
GO(dbus_pending_call_free_data_slot, vFp)
GO(dbus_pending_call_get_completed, iFp)
GO(dbus_pending_call_get_data, pFpi)
GO(dbus_pending_call_ref, pFp)
GOM(dbus_pending_call_set_data, iFEpipp)
GOM(dbus_pending_call_set_notify, iFEpppp)
GO(dbus_pending_call_steal_reply, pFp)
GO(dbus_pending_call_unref, vFp)
//GO(dbus_realloc, 
//GO(dbus_server_allocate_data_slot, 
//GO(dbus_server_disconnect, 
//GO(dbus_server_free_data_slot, 
//GO(dbus_server_get_address, 
//GO(dbus_server_get_data, 
//GO(dbus_server_get_id, 
//GO(dbus_server_get_is_connected, 
//GO(dbus_server_listen, 
//GO(dbus_server_ref, 
//GO(dbus_server_set_auth_mechanisms, 
//GO(dbus_server_set_data, 
//GO(dbus_server_set_new_connection_function, 
//GO(dbus_server_set_timeout_functions, 
//GO(dbus_server_set_watch_functions, 
//GO(dbus_server_unref, 
GO(dbus_set_error, vFpppppppppp)    //vaarg
GO(dbus_set_error_const, vFppp)
GO(dbus_set_error_from_message, iFpp)
//GO(dbus_shutdown, 
//GO(dbus_signature_iter_get_current_type, 
//GO(dbus_signature_iter_get_element_type, 
//GO(dbus_signature_iter_get_signature, 
//GO(dbus_signature_iter_init, 
//GO(dbus_signature_iter_next, 
//GO(dbus_signature_iter_recurse, 
//GO(dbus_signature_validate, 
//GO(dbus_signature_validate_single, 
//GO(dbus_threads_init, 
//GO(dbus_threads_init_default, 
GO(dbus_timeout_get_data, pFp)
GO(dbus_timeout_get_enabled, iFp)
GO(dbus_timeout_get_interval, iFp)
GO(dbus_timeout_handle, iFp)
GOM(dbus_timeout_set_data, vFppp)
//GO(dbus_type_is_basic, 
//GO(dbus_type_is_container, 
//GO(dbus_type_is_fixed, 
//GO(dbus_watch_get_data, 
//GO(dbus_watch_get_enabled, 
//GO(dbus_watch_get_fd, 
//GO(dbus_watch_get_flags, 
//GO(dbus_watch_get_socket, 
//GO(dbus_watch_get_unix_fd, 
//GO(dbus_watch_handle, 
//GO(dbus_watch_set_data, 