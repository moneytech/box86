#if !(defined(GO) && defined(GOM) && defined(GO2) && defined(DATA))
#error meh!
#endif

//GO(FT_Activate_Size, 
//GO(FT_Add_Default_Modules, 
//GO(FT_Add_Module, 
GO(FT_Angle_Diff, lFll)
GO(FT_Atan2, lFll)
GO(FT_Attach_File, iFpp)
GO(FT_Attach_Stream, iFpp)
//GO(FT_Bitmap_Convert, 
//GO(FT_Bitmap_Copy, 
//GO(FT_Bitmap_Done, 
//GO(FT_Bitmap_Embolden, 
//GO(FT_Bitmap_Init, 
//GO(FT_Bitmap_New, 
//GO(FTC_CMapCache_Lookup, 
//GO(FTC_CMapCache_New, 
//GO(FT_CeilFix, 
//GO(FTC_ImageCache_Lookup, 
//GO(FTC_ImageCache_LookupScaler, 
//GO(FTC_ImageCache_New, 
//GO(FT_ClassicKern_Free, 
//GO(FT_ClassicKern_Validate, 
//GO(FTC_Manager_Done, 
//GO(FTC_Manager_LookupFace, 
//GO(FTC_Manager_LookupSize, 
//GO(FTC_Manager_New, 
//GO(FTC_Manager_RemoveFaceID, 
//GO(FTC_Manager_Reset, 
//GO(FTC_Node_Unref, 
GO(FT_Cos, lFl)
//GO(FTC_SBitCache_Lookup, 
//GO(FTC_SBitCache_LookupScaler, 
//GO(FTC_SBitCache_New, 
//GO(FT_DivFix, 
GO(FT_Done_Face, iFp)
GO(FT_Done_FreeType, iFp)
GO(FT_Done_Glyph, vFp)
GO(FT_Done_Library, iFp)
//GO(FT_Done_Size, 
//GO(FT_Face_CheckTrueTypePatents, 
//GO(FT_Face_GetCharsOfVariant, 
//GO(FT_Face_GetCharVariantIndex, 
//GO(FT_Face_GetCharVariantIsDefault, 
//GO(FT_Face_GetVariantSelectors, 
//GO(FT_Face_GetVariantsOfChar, 
GO(FT_Face_Properties, iFpup)
//GO(FT_Face_SetUnpatentedHinting, 
//GO(FT_FloorFix, 
//GO(FT_Get_Advance, 
//GO(FT_Get_Advances, 
//GO(FT_Get_BDF_Charset_ID, 
//GO(FT_Get_BDF_Property, 
GO(FT_Get_Char_Index, uFpL)
GO(FT_Get_Charmap_Index, iFp)
//GO(FT_Get_CID_From_Glyph_Index, 
//GO(FT_Get_CID_Is_Internally_CID_Keyed, 
//GO(FT_Get_CID_Registry_Ordering_Supplement, 
//GO(FT_Get_CMap_Format, 
//GO(FT_Get_CMap_Language_ID, 
GO(FT_Get_First_Char, LFpp)
//GO(FT_Get_Font_Format, 
GO(FT_Get_FSType_Flags, WFp)
//GO(FT_Get_Gasp, 
GO(FT_Get_Glyph, iFpp)
GO(FT_Get_Glyph_Name, iFpupu)
GO(FT_Get_Kerning, iFpuuup)
//GO(FT_Get_MM_Blend_Coordinates, 
//GO(FT_Get_MM_Var, 
//GO(FT_Get_Module, 
//GO(FT_Get_Multi_Master, 
GO(FT_Get_Name_Index, uFpp)
GO(FT_Get_Next_Char, LFpLp)
//GO(FT_Get_PFR_Advance, 
//GO(FT_Get_PFR_Kerning, 
//GO(FT_Get_PFR_Metrics, 
GO(FT_Get_Postscript_Name, pFp)
GO(FT_Get_PS_Font_Info, iFpp)
//GO(FT_Get_PS_Font_Private, 
//GO(FT_Get_PS_Font_Value, 
//GO(FT_Get_Renderer, 
//GO(FT_Get_Sfnt_LangTag, 
//GO(FT_Get_Sfnt_Name, 
//GO(FT_Get_Sfnt_Name_Count, 
GO(FT_Get_Sfnt_Table, pFpi)
GO(FT_Get_SubGlyph_Info, iFpuppppp)
GO(FT_Get_Track_Kerning, iFplip)
//GO(FT_Get_TrueType_Engine_Type, 
//GO(FT_Get_Var_Blend_Coordinates, 
//GO(FT_Get_Var_Design_Coordinates, 
//GO(FT_Get_WinFNT_Header, 
//GO(FT_Get_X11_Font_Format, 
GO(FT_Glyph_Copy, iFpp)
GO(FT_Glyph_Get_CBox, vFpup)
GO(FT_GlyphSlot_Embolden, vFp)
GO(FT_GlyphSlot_Oblique, vFp)
//GO(FT_GlyphSlot_Own_Bitmap, 
//GO(FT_Glyph_Stroke, 
GO(FT_Glyph_StrokeBorder, iFppCC)
GO(FT_Glyph_To_Bitmap, iFpipC)
GO(FT_Glyph_Transform, iFppp)
//GO(FT_Gzip_Uncompress, 
//GO(FT_Has_PS_Glyph_Names, 
GO(FT_Init_FreeType, iFp)
//GO(FT_Library_SetLcdFilter, 
//GO(FT_Library_SetLcdFilterWeights, 
//GO(FT_Library_Version, 
//GO(FT_List_Add, 
//GO(FT_List_Finalize, 
//GO(FT_List_Find, 
//GO(FT_List_Insert, 
//GO(FT_List_Iterate, 
//GO(FT_List_Remove, 
//GO(FT_List_Up, 
GO(FT_Load_Char, iFpLi)
GO(FT_Load_Glyph, iFpui)
GO(FT_Load_Sfnt_Table, iFpLlpp)
GO(FT_Matrix_Invert, iFp)
GO(FT_Matrix_Multiply, vFpp)
GO(FT_MulDiv, lFlll)
GO(FT_MulFix, lFll)
GO(FT_New_Face, iFpplp)
//GO(FT_New_Library, 
GO(FT_New_Memory_Face, iFppllp)
//GO(FT_New_Size, 
GOM(FT_Open_Face, iFEpplp)
//GO(FT_OpenType_Free, 
//GO(FT_OpenType_Validate, 
GO(FT_Outline_Check, iFp)
GO(FT_Outline_Copy, iFpp)
GO(FT_Outline_Decompose, iFppp)
//GO(FT_Outline_Done, 
//GO(FT_Outline_Done_Internal, 
GO(FT_Outline_Embolden, iFpl)
GO(FT_Outline_EmboldenXY, iFpll)
GO(FT_Outline_Get_BBox, iFpp)
GO(FT_Outline_Get_Bitmap, iFppp)
GO(FT_Outline_Get_CBox, vFpp)
//GO(FT_Outline_GetInsideBorder, 
//GO(FT_Outline_Get_Orientation, 
//GO(FT_Outline_GetOutsideBorder, 
//GO(FT_Outline_New, 
//GO(FT_Outline_New_Internal, 
GO(FT_Outline_Render, iFppp)
GO(FT_Outline_Reverse, vFp)
GO(FT_Outline_Transform, vFpp)
GO(FT_Outline_Translate, vFpll)
//GO(FT_Property_Get, 
//GO(FT_Property_Set, 
GO(FT_Reference_Face, iFp)
//GO(FT_Reference_Library, 
//GO(FT_Remove_Module, 
GO(FT_Render_Glyph, iFpi)
GO(FT_Request_Size, iFpp)
//GO(FT_RoundFix, 
GO(FT_Select_Charmap, iFpi)
GO(FT_Select_Size, iFpi)
GO(FT_Set_Charmap, iFpp)
GO(FT_Set_Char_Size, iFplluu)
//GO(FT_Set_Debug_Hook, 
//GO(FT_Set_Default_Properties, 
//GO(FT_Set_MM_Blend_Coordinates, 
//GO(FT_Set_MM_Design_Coordinates, 
GO(FT_Set_Pixel_Sizes, iFpuu)
//GO(FT_Set_Renderer, 
GO(FT_Set_Transform, vFppp)
//GO(FT_Set_Var_Blend_Coordinates, 
//GO(FT_Set_Var_Design_Coordinates, 
//GO(FT_Sfnt_Table_Info, 
GO(FT_Sin, lFl)
//GO(FT_Stream_OpenBzip2, 
//GO(FT_Stream_OpenGzip, 
//GO(FT_Stream_OpenLZW, 
GO(FT_Stroker_BeginSubPath, iFppC)
GO(FT_Stroker_ConicTo, iFppp)
GO(FT_Stroker_CubicTo, iFpppp)
GO(FT_Stroker_Done, vFp)
GO(FT_Stroker_EndSubPath, iFp)
GO(FT_Stroker_Export, vFpp)
GO(FT_Stroker_ExportBorder, vFpip)
GO(FT_Stroker_GetBorderCounts, iFpipp)
GO(FT_Stroker_GetCounts, iFppp)
GO(FT_Stroker_LineTo, iFpp)
GO(FT_Stroker_New, iFpp)
GO(FT_Stroker_ParseOutline, iFppC)
GO(FT_Stroker_Rewind, vFp)
GO(FT_Stroker_Set, vFpliil)
GO(FT_Tan, lFl)
//GO(FT_TrueTypeGX_Free, 
//GO(FT_TrueTypeGX_Validate, 
GO(FT_Vector_From_Polar, vFpll)
GO(FT_Vector_Length, lFp)
GO(FT_Vector_Polarize, vFppp)
GO(FT_Vector_Rotate, vFpl)
GO(FT_Vector_Transform, vFpp)
GO(FT_Vector_Unit, vFpl)
//GO(TT_New_Context, 
//GO(TT_RunIns, 
