#if !(defined(GO) && defined(GOM) && defined(GO2) && defined(DATA))
#error Meh....
#endif

GOM(curl_easy_cleanup, vFEp)
//GO(curl_easy_duphandle, 
GO(curl_easy_escape, pFppi)
GO(curl_easy_getinfo, uFpppppp) //vararg
GO(curl_easy_init, pFv)
//GO(curl_easy_pause, 
GO(curl_easy_perform, uFp)
//GO(curl_easy_recv, 
GO(curl_easy_reset, vFp)
//GO(curl_easy_send, 
GOM(curl_easy_setopt, uFEpup)   // can set many callbacks!
GO(curl_easy_strerror, pFu)
//GO(curl_easy_unescape, 
//GO(curl_escape, 
GO(curl_formadd, iFpppppppppppppppp)    // there is a vararg here. Should GOM and use CURLFORM_ARRAY instead
GO(curl_formfree, vFp)
//GO(curl_formget, 
//GO(curl_free, 
//GO(curl_getdate, 
//GO(curl_getenv, 
GO(curl_global_cleanup, vFv)
GO(curl_global_init, uFu)
//GO(curl_global_init_mem, 
//GO(curl_global_sslset, 
//GO(curl_maprintf, 
//GO(curl_mfprintf, 
//GO(curl_mime_addpart, 
//GO(curl_mime_data, 
//GO(curl_mime_data_cb, 
//GO(curl_mime_encoder, 
//GO(curl_mime_filedata, 
//GO(curl_mime_filename, 
//GO(curl_mime_free, 
//GO(curl_mime_headers, 
//GO(curl_mime_init, 
//GO(curl_mime_name, 
//GO(curl_mime_subparts, 
//GO(curl_mime_type, 
//GO(curl_mprintf, 
//GO(curl_msnprintf, 
//GO(curl_msprintf, 
GO(curl_multi_add_handle, uFpp)
//GO(curl_multi_assign, 
GO(curl_multi_cleanup, uFp)
GO(curl_multi_fdset, uFppppp)
GO(curl_multi_info_read, pFpp)
GO(curl_multi_init, pFv)
GO(curl_multi_perform, uFpp)
GO(curl_multi_remove_handle, uFpp)
//GO(curl_multi_setopt, 
//GO(curl_multi_socket, 
//GO(curl_multi_socket_action, 
//GO(curl_multi_socket_all, 
//GO(curl_multi_strerror, 
//GO(curl_multi_timeout, 
//GO(curl_multi_wait, 
//GO(curl_mvaprintf, 
//GO(curl_mvfprintf, 
//GO(curl_mvprintf, 
//GO(curl_mvsnprintf, 
//GO(curl_mvsprintf, 
//GO(curl_pushheader_byname, 
//GO(curl_pushheader_bynum, 
//GO(curl_share_cleanup, 
//GO(curl_share_init, 
//GO(curl_share_setopt, 
//GO(curl_share_strerror, 
GO(curl_slist_append, pFpp)
GO(curl_slist_free_all, vFp)
//GO(curl_strequal, 
//GO(curl_strnequal, 
//GO(curl_unescape, 
//GO(curl_version, 
//GO(curl_version_info, 
