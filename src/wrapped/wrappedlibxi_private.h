#if !(defined(GO) && defined(GOM) && defined(GO2) && defined(DATA))
#error Meh....
#endif

//GO(XAllowDeviceEvents, 
//GO(XChangeDeviceControl, 
//GO(XChangeDeviceDontPropagateList, 
//GO(XChangeDeviceKeyMapping, 
GO(XChangeDeviceProperty, vFppppiipi)
//GO(XChangeFeedbackControl, 
//GO(XChangeKeyboardDevice, 
//GO(XChangePointerDevice, 
GO(XCloseDevice, iFpp)
GO(XDeleteDeviceProperty, vFppp)
//GO(XDeviceBell, 
//GO(XFreeDeviceControl, 
GO(XFreeDeviceList, iFp)
GO(XFreeDeviceMotionEvents, iFv)
GO(XFreeDeviceState, vFp)
//GO(XFreeFeedbackList, 
//GO(XGetDeviceButtonMapping, 
//GO(XGetDeviceControl, 
//GO(XGetDeviceDontPropagateList, 
//GO(XGetDeviceFocus, 
//GO(XGetDeviceKeyMapping, 
//GO(XGetDeviceModifierMapping, 
GO(XGetDeviceMotionEvents, pFppuuppp)
GO(XGetDeviceProperty, iFpppllipppppp)
//GO(XGetExtensionVersion, 
//GO(XGetFeedbackControl, 
//GO(XGetSelectedExtensionEvents, 
GO(XGrabDevice, iFpppiipiiu)
//GO(XGrabDeviceButton, 
//GO(XGrabDeviceKey, 
//GO(XIAllowEvents, 
//GO(XIAllowTouchEvents, 
//GO(XIBarrierReleasePointer, 
//GO(XIBarrierReleasePointers, 
//GO(XIChangeHierarchy, 
GO(XIChangeProperty, vFpippiipi)
//GO(XIDefineCursor, 
GO(XIDeleteProperty, vFpip)
GO(XIFreeDeviceInfo, vFp)
//GO(XIGetClientPointer, 
//GO(XIGetFocus, 
GO(XIGetProperty, iFpipllippppp)
GO(XIGetSelectedEvents, iFpppi)
//GO(XIGrabButton, 
GO(XIGrabDevice, iFpipLpiiip)
//GO(XIGrabEnter, 
//GO(XIGrabFocusIn, 
//GO(XIGrabKeycode, 
//GO(XIGrabTouchBegin, 
//GO(XIListProperties, 
GO(XIQueryDevice, pFpip)
GO(XIQueryPointer, iFpipppppppppp)
GO(XIQueryVersion, iFppp)
GO(XISelectEvents, iFpppi)
//GO(XISetClientPointer, 
//GO(XISetFocus, 
//GO(XIUndefineCursor, 
//GO(XIUngrabButton, 
GO(XIUngrabDevice, iFpiL)
//GO(XIUngrabEnter, 
//GO(XIUngrabFocusIn, 
//GO(XIUngrabKeycode, 
//GO(XIUngrabTouchBegin, 
//GO(XIWarpPointer, 
//GO(XListDeviceProperties, 
GO(XListInputDevices, pFpp)
GO(XOpenDevice, pFpp)
GO(XQueryDeviceState, pFpp)
GO(XSelectExtensionEvent, iFpppi)
//GO(XSendExtensionEvent, 
//GO(XSetDeviceButtonMapping, 
//GO(XSetDeviceFocus, 
//GO(XSetDeviceMode, 
//GO(XSetDeviceModifierMapping, 
//GO(XSetDeviceValuators, 
GO(XUngrabDevice, iFppu)
//GO(XUngrabDeviceButton, 
//GO(XUngrabDeviceKey, 
//GO(_XiGetDevicePresenceNotifyEvent, 
//GO(_xibadclass, 
//GO(_xibaddevice, 
//GO(_xibadevent, 
//GO(_xibadmode, 
//GO(_xidevicebusy, 
