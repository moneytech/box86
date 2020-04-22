#if !(defined(GO) && defined(GOM) && defined(GO2) && defined(DATA))
#error Meh...
#endif

GO(pa_ascii_filter, pFp)
GO(pa_ascii_valid, pFp)
GO(pa_bytes_per_second, uFp)
GO(pa_bytes_snprint, pFpuu)
GO(pa_bytes_to_usec, UFUp)
GO(pa_channel_map_can_balance, iFp)
GO(pa_channel_map_can_fade, iFp)
GO(pa_channel_map_compatible, iFpp)
GO(pa_channel_map_equal, iFpp)
GO(pa_channel_map_init, pFp)
GO(pa_channel_map_init_auto, pFpui)
GO(pa_channel_map_init_extend, pFpui)
GO(pa_channel_map_init_mono, pFp)
GO(pa_channel_map_init_stereo, pFp)
GO(pa_channel_map_parse, pFpp)
GO(pa_channel_map_snprint, pFpup)
GO(pa_channel_map_superset, iFpp)
GO(pa_channel_map_to_name, pFp)
GO(pa_channel_map_to_pretty_name, pFp)
GO(pa_channel_map_valid, iFp)
GO(pa_channel_position_to_pretty_string, pFi)
GO(pa_channel_position_to_string, pFi)
//GO(pa_context_add_autoload, 
GOM(pa_context_connect, iFEppip)
GO(pa_context_disconnect, vFp)
GOM(pa_context_drain, pFEppp)
GO(pa_context_errno, iFp)
GOM(pa_context_exit_daemon, pFEppp)
//GO(pa_context_get_autoload_info_by_index, 
//GO(pa_context_get_autoload_info_by_name, 
//GO(pa_context_get_autoload_info_list, 
//GO(pa_context_get_card_info_by_index, 
//GO(pa_context_get_card_info_by_name, 
//GO(pa_context_get_card_info_list, 
//GO(pa_context_get_client_info, 
//GO(pa_context_get_client_info_list, 
GO(pa_context_get_index, uFp)
//GO(pa_context_get_module_info, 
GOM(pa_context_get_module_info_list, pFEppp)
GO(pa_context_get_protocol_version, uFp)
//GO(pa_context_get_sample_info_by_index, 
//GO(pa_context_get_sample_info_by_name, 
//GO(pa_context_get_sample_info_list, 
GO(pa_context_get_server, pFp)
GOM(pa_context_get_server_info, pFEppp)
GO(pa_context_get_server_protocol_version, uFp)
GOM(pa_context_get_sink_info_by_index, pFEpupp)
GOM(pa_context_get_sink_info_by_name, pFEpppp)
GOM(pa_context_get_sink_info_list, pFEppp)
//GO(pa_context_get_sink_input_info, 
GOM(pa_context_get_sink_input_info_list, pFEppp)
GOM(pa_context_get_source_info_by_index, pFEpupp)
GOM(pa_context_get_source_info_by_name, pFEpppp)
GOM(pa_context_get_source_info_list, pFEppp)
//GO(pa_context_get_source_output_info, 
//GO(pa_context_get_source_output_info_list, 
GO(pa_context_get_state, iFp)
GO(pa_context_is_local, iFp)
GO(pa_context_is_pending, iFp)
//GO(pa_context_kill_client, 
//GO(pa_context_kill_sink_input, 
//GO(pa_context_kill_source_output, 
GOM(pa_context_load_module, pFEppppp)
GOM(pa_context_move_sink_input_by_index, pFEpuupp)
//GO(pa_context_move_sink_input_by_name, 
//GO(pa_context_move_source_output_by_index, 
//GO(pa_context_move_source_output_by_name, 
GOM(pa_context_new, pFEpp)
GOM(pa_context_new_with_proplist, pFEppp)
//GO(pa_context_play_sample, 
//GO(pa_context_play_sample_with_proplist, 
GOM(pa_context_proplist_remove, pFEpppp)
GOM(pa_context_proplist_update, pFEpippp)
GO(pa_context_ref, pFp)
//GO(pa_context_remove_autoload_by_index, 
//GO(pa_context_remove_autoload_by_name, 
//GO(pa_context_remove_sample, 
//GO(pa_context_set_card_profile_by_index, 
//GO(pa_context_set_card_profile_by_name, 
GOM(pa_context_set_default_sink, pFEpppp)
GOM(pa_context_set_default_source, pFEpppp)
GOM(pa_context_set_event_callback, vFEppp)
GOM(pa_context_set_name, pFEpppp)
//GO(pa_context_set_sink_input_mute, 
//GO(pa_context_set_sink_input_volume, 
//GO(pa_context_set_sink_mute_by_index, 
//GO(pa_context_set_sink_mute_by_name, 
//GO(pa_context_set_sink_volume_by_index, 
//GO(pa_context_set_sink_volume_by_name, 
//GO(pa_context_set_source_mute_by_index, 
//GO(pa_context_set_source_mute_by_name, 
//GO(pa_context_set_source_volume_by_index, 
GOM(pa_context_set_source_volume_by_name, pFEppppp)
GOM(pa_context_set_state_callback, vFEppp)
GOM(pa_context_set_subscribe_callback, vFEppp)
//GO(pa_context_stat, 
GOM(pa_context_subscribe, pFEpupp)
//GO(pa_context_suspend_sink_by_index, 
//GO(pa_context_suspend_sink_by_name, 
//GO(pa_context_suspend_source_by_index, 
//GO(pa_context_suspend_source_by_name, 
GOM(pa_context_unload_module, pFEpupp)
GO(pa_context_unref, vFp)
GO(pa_cvolume_avg, uFp)
GO(pa_cvolume_channels_equal_to, iFpu)
GO(pa_cvolume_compatible, iFpp)
GO(pa_cvolume_compatible_with_channel_map, iFpp)
GO(pa_cvolume_equal, iFpp)
GO(pa_cvolume_get_balance, fFpp)
GO(pa_cvolume_get_fade, fFpp)
GO(pa_cvolume_init, pFp)
GO(pa_cvolume_max, uFp)
GO(pa_cvolume_remap, pFppp)
GO(pa_cvolume_scale, pFpu)
GO(pa_cvolume_set, pFpuu)
GO(pa_cvolume_set_balance, pFppf)
GO(pa_cvolume_set_fade, pFppf)
GO(pa_cvolume_snprint, pFpup)
GO(pa_cvolume_valid, iFp)
//GO(pa_ext_stream_restore_delete, 
//GO(pa_ext_stream_restore_read, 
//GO(pa_ext_stream_restore_set_subscribe_cb, 
//GO(pa_ext_stream_restore_subscribe, 
//GO(pa_ext_stream_restore_test, 
//GO(pa_ext_stream_restore_write, 
GO(pa_frame_size, uFp)
GO(pa_get_binary_name, pFpL)
GO(pa_get_fqdn, pFpL)
GO(pa_get_home_dir, pFpL)
GO(pa_get_host_name, pFpL)
GO(pa_get_library_version, pFv)
GO(pa_gettimeofday, pFp)
GO(pa_get_user_name, pFpL)
//GO(pa_locale_to_utf8, 
//GO(pa_mainloop_api_once, 
GO(pa_mainloop_dispatch, iFp)
GOM(pa_mainloop_free, vFEp)
GOM(pa_mainloop_get_api, pFEp)
GO(pa_mainloop_get_retval, iFp)
GO(pa_mainloop_iterate, iFpip)
GO(pa_mainloop_new, pFv)
GO(pa_mainloop_poll, iFp)
GO(pa_mainloop_prepare, iFpi)
GO(pa_mainloop_quit, vFpi)
GO(pa_mainloop_run, iFpp)
//GO(pa_mainloop_set_poll_func, vFpBp)  //B is typedef int(*pa_poll_func) (struct pollfd *ufds, unsigned long nfds, int timeout, void *userdata)
GO(pa_mainloop_wakeup, vFp)
//GO(pa_msleep, 
GO(pa_operation_cancel, vFp)
GO(pa_operation_get_state, iFp)
GO(pa_operation_ref, pFp)
GO(pa_operation_unref, vFp)
GO(pa_parse_sample_format, iFp)
GO(pa_path_get_filename, pFp)
//GO(pa_proplist_clear, 
//GO(pa_proplist_contains, 
//GO(pa_proplist_copy, 
GO(pa_proplist_free, vFp)
//GO(pa_proplist_from_string, 
//GO(pa_proplist_get, 
GO(pa_proplist_gets, pFpp)
//GO(pa_proplist_isempty, 
//GO(pa_proplist_iterate, 
GO(pa_proplist_new, pFv)
GO(pa_proplist_set, iFpppu)
GOM(pa_proplist_setf, iFEpppV)
GO(pa_proplist_sets, iFppp)
GO(pa_proplist_size, uFp)
GO(pa_proplist_to_string, pFp)
GO(pa_proplist_to_string_sep, pFpp)
GO(pa_proplist_unset, iFpp)
GO(pa_proplist_unset_many, iFpp)
GO(pa_proplist_update, vFpip)
GO(pa_sample_format_to_string, pFi)
GO(pa_sample_size, uFp)
GO(pa_sample_size_of_format, uFp)
GO(pa_sample_spec_equal, iFpp)
GO(pa_sample_spec_init, pFp)
GO(pa_sample_spec_snprint, pFpup)
GO(pa_sample_spec_valid, iFp)
GO(pa_signal_done, vFv)
GO(pa_signal_free, vFp)
GOM(pa_signal_init, iFEp)
GOM(pa_signal_new, pFEipp)
GOM(pa_signal_set_destroy, vFEpp)
GO(pa_stream_connect_playback, iFpppipp)
GO(pa_stream_connect_record, iFpppi)
GO(pa_stream_connect_upload, iFpu)
GOM(pa_stream_cork, pFEpipp)
GO(pa_stream_disconnect, iFp)
GOM(pa_stream_drain, pFEppp)
GO(pa_stream_drop, iFp)
GO(pa_stream_finish_upload, iFp)
GOM(pa_stream_flush, pFEppp)
GO(pa_stream_get_buffer_attr, pFp)
GO(pa_stream_get_channel_map, pFp)
GO(pa_stream_get_context, pFp)
GO(pa_stream_get_device_index, uFp)
GO(pa_stream_get_device_name, pFp)
GO(pa_stream_get_index, uFp)
GO(pa_stream_get_latency, iFppp)
GO(pa_stream_get_monitor_stream, uFp)
GO(pa_stream_get_sample_spec, pFp)
GO(pa_stream_get_state, iFp)
GO(pa_stream_get_time, iFpp)
GO(pa_stream_get_timing_info, pFp)
GO(pa_stream_is_corked, iFp)
GO(pa_stream_is_suspended, iFp)
GO(pa_stream_new, pFpppp)
GO(pa_stream_new_with_proplist, pFppppp)
GO(pa_stream_peek, iFppp)
GOM(pa_stream_prebuf, pFEppp)
GOM(pa_stream_proplist_remove, pFEpppp)
GOM(pa_stream_proplist_update, pFEpippp)
GO(pa_stream_readable_size, uFp)
GO(pa_stream_ref, pFp)
GOM(pa_stream_set_buffer_attr, pFEpppp)
GOM(pa_stream_set_buffer_attr_callback, vFEppp)
GOM(pa_stream_set_event_callback, vFEppp)
GOM(pa_stream_set_latency_update_callback, vFEppp)
GO(pa_stream_set_monitor_stream, iFpu)
GOM(pa_stream_set_moved_callback, vFEppp)
GOM(pa_stream_set_name, pFEpppp)
GOM(pa_stream_set_overflow_callback, vFEppp)
GOM(pa_stream_set_read_callback, vFEppp)
GOM(pa_stream_set_started_callback, vFEppp)
GOM(pa_stream_set_state_callback, vFEppp)
GOM(pa_stream_set_suspended_callback, vFEppp)
GOM(pa_stream_set_underflow_callback, vFEppp)
GOM(pa_stream_set_write_callback, vFEppp)
GOM(pa_stream_trigger, pFEppp)
GO(pa_stream_unref, vFp)
GOM(pa_stream_update_sample_rate, pFEpupp)
GOM(pa_stream_update_timing_info, pFEppp)
GO(pa_stream_writable_size, uFp)
GOM(pa_stream_write, iFEppupIi)
GO(pa_strerror, pFi)
GO(pa_sw_cvolume_divide, pFppp)
GO(pa_sw_cvolume_multiply, pFppp)
GO(pa_sw_cvolume_snprint_dB, pFpup)
GO(pa_sw_volume_divide, uFuu)
GO(pa_sw_volume_from_dB, uFd)
GO(pa_sw_volume_from_linear, uFd)
GO(pa_sw_volume_multiply, uFuu)
GO(pa_sw_volume_snprint_dB, pFpuu)
GO(pa_sw_volume_to_dB, dFu)
GO(pa_sw_volume_to_linear, dFu)
GO(pa_threaded_mainloop_accept, vFp)
GOM(pa_threaded_mainloop_free, vFEp)
GOM(pa_threaded_mainloop_get_api, pFEp)
GO(pa_threaded_mainloop_get_retval, iFp)
GO(pa_threaded_mainloop_in_thread, iFp)
GO(pa_threaded_mainloop_lock, vFp)
GO(pa_threaded_mainloop_new, pFv)
GO(pa_threaded_mainloop_signal, vFpi)
GO(pa_threaded_mainloop_start, iFp)
GO(pa_threaded_mainloop_stop, vFp)
GO(pa_threaded_mainloop_unlock, vFp)
GO(pa_threaded_mainloop_wait, vFp)
GO(pa_timeval_add, pFpU)
GO(pa_timeval_age, UFp)
GO(pa_timeval_cmp, iFpp)
GO(pa_timeval_diff, UFpp)
GO(pa_timeval_load, UFp)
GO(pa_timeval_store, pFpU)
GO(pa_timeval_sub, pFpU)
GO(pa_usec_to_bytes, uFUp)
GO(pa_utf8_filter, pFp)
GO(pa_utf8_to_locale, pFp)
GO(pa_utf8_valid, pFp)
GO(pa_volume_snprint, pFpuu)
GO(pa_xfree, vFp)
GO(pa_xmalloc, pFu)
GO(pa_xmalloc0, pFu)
GO(pa_xmemdup, pFpu)
GO(pa_xrealloc, pFpu)
GO(pa_xstrdup, pFp)
GO(pa_xstrndup, pFpu)

GO(pa_stream_begin_write, iFppp)	// 0.9.16+

GO(dummy_io_new, pFpiipp)   // dumy function to create Wrapper