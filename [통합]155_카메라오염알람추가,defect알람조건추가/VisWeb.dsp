# Microsoft Developer Studio Project File - Name="VisWeb" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VisWeb - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VisWeb.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VisWeb.mak" CFG="VisWeb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VisWeb - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VisWeb - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VisWeb - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 WS2_32.lib FChainDLL.lib NeSerial.lib MIl.lib /nologo /subsystem:windows /machine:I386 /out:"VisWeb.exe"

!ELSEIF  "$(CFG)" == "VisWeb - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 FChainDLL.lib NeSerial.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "VisWeb - Win32 Release"
# Name "VisWeb - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\Data.cpp
# End Source File
# Begin Source File

SOURCE=.\Disk_File.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\DlgGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\Fchain.cpp
# End Source File
# Begin Source File

SOURCE=.\FileMove1.cpp
# End Source File
# Begin Source File

SOURCE=.\FindEdge.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\Image.cpp
# End Source File
# Begin Source File

SOURCE=.\ini.cpp
# End Source File
# Begin Source File

SOURCE=.\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\InPlaceList.cpp
# End Source File
# Begin Source File

SOURCE=.\Inspect.cpp
# End Source File
# Begin Source File

SOURCE=.\Label1.cpp
# End Source File
# Begin Source File

SOURCE=.\LogData.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ReedSolomon.cpp
# End Source File
# Begin Source File

SOURCE=.\Shutdown_Library.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemClock.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\TimingProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\Vision.cpp
# End Source File
# Begin Source File

SOURCE=.\VisWeb.cpp
# End Source File
# Begin Source File

SOURCE=.\VisWeb.rc
# End Source File
# Begin Source File

SOURCE=.\VisWebDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\VisWebView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\Data.h
# End Source File
# Begin Source File

SOURCE=.\Disk_File.h
# End Source File
# Begin Source File

SOURCE=.\DlgGrid.h
# End Source File
# Begin Source File

SOURCE=.\DlgInterface.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetting.h
# End Source File
# Begin Source File

SOURCE=.\Fchain.h
# End Source File
# Begin Source File

SOURCE=.\FchainDll.h
# End Source File
# Begin Source File

SOURCE=.\FileMove1.h
# End Source File
# Begin Source File

SOURCE=.\FindEdge.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\Image.h
# End Source File
# Begin Source File

SOURCE=.\ini.h
# End Source File
# Begin Source File

SOURCE=.\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\InPlaceList.h
# End Source File
# Begin Source File

SOURCE=.\Inspect.h
# End Source File
# Begin Source File

SOURCE=.\Label1.h
# End Source File
# Begin Source File

SOURCE=.\LogData.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\NeProtocol.h
# End Source File
# Begin Source File

SOURCE=.\ReedSolomon.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Shutdown_Library.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemClock.h
# End Source File
# Begin Source File

SOURCE=.\TimingProcess.h
# End Source File
# Begin Source File

SOURCE=.\Vision.h
# End Source File
# Begin Source File

SOURCE=.\VisWeb.h
# End Source File
# Begin Source File

SOURCE=.\VisWebDoc.h
# End Source File
# Begin Source File

SOURCE=.\VisWebView.h
# End Source File
# Begin Source File

SOURCE=.\WinSerial.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VisWeb.ico
# End Source File
# Begin Source File

SOURCE=.\res\VisWeb.rc2
# End Source File
# Begin Source File

SOURCE=.\res\VisWebDoc.ico
# End Source File
# End Group
# Begin Group "UdpNetwork"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Udp_Network_module\Packet.cpp
# End Source File
# Begin Source File

SOURCE=.\Udp_Network_module\Packet.h
# End Source File
# Begin Source File

SOURCE=.\Udp_Network_module\XManageSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Udp_Network_module\XManageSocket.h
# End Source File
# Begin Source File

SOURCE=.\Udp_Network_module\XSocketComm.cpp
# End Source File
# Begin Source File

SOURCE=.\Udp_Network_module\XSocketComm.h
# End Source File
# End Group
# Begin Group "KYW"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SlitAreaDocument.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=".\개발기록.txt"
# End Source File
# Begin Source File

SOURCE=.\mil.lib
# End Source File
# Begin Source File

SOURCE=.\VERSION.LIB
# End Source File
# Begin Source File

SOURCE=.\WS2_32.LIB
# End Source File
# End Target
# End Project
# Section VisWeb : {001C72A5-D273-4058-8AF2-273E38E4E198}
# 	2:14:SocketData.cpp:SocketData.cpp
# 	2:18:CLASS: CSocketData:CSocketData
# 	2:12:SocketData.h:SocketData.h
# 	2:19:Application Include:VisWeb.h
# End Section
# Section VisWeb : {394047EF-6896-434D-8088-E3CBB1BBB488}
# 	2:8:Label1.h:Label1.h
# 	2:13:CLASS: CLabel:CLabel
# 	2:10:Label1.cpp:Label1.cpp
# 	2:15:ENUM: FlashType:FlashType
# 	2:19:Application Include:VisWeb.h
# End Section
# Section VisWeb : {10E4FF9F-A4C9-42F3-8CD9-08E84CE84461}
# 	2:12:DataSocket.h:DataSocket.h
# 	2:18:CLASS: CDataSocket:CDataSocket
# 	2:14:DataSocket.cpp:DataSocket.cpp
# 	2:19:Application Include:VisWeb.h
# End Section
# Section VisWeb : {A7166D66-7CA6-4C28-BBAB-FD56636C7FB4}
# 	2:10:ENUM: enum:enum
# 	2:16:CLASS: CButtonST:CButtonST
# 	2:9:BtnST.cpp:BtnST.cpp
# 	2:19:Application Include:VisWeb.h
# 	2:7:BtnST.h:BtnST.h
# End Section
# Section VisWeb : {5E8BAEF7-3197-4CD8-A5B7-5D218D6D2FAB}
# 	2:18:TYPEDEF: LPMESSAGE:LPMESSAGE
# 	2:17:CLASS: tagMessage:tagMessage
# 	2:15:CLASS: CNetwork:CNetwork
# 	2:11:Network.cpp:Network.cpp
# 	2:9:Network.h:Network.h
# 	2:16:TYPEDEF: MESSAGE:MESSAGE
# 	2:19:Application Include:VisWeb.h
# End Section
# Section VisWeb : {AFD34472-72B0-44DD-9FCE-0A52FAC3EDBF}
# 	2:19:CLASS: CInPlaceEdit:CInPlaceEdit
# 	2:15:InPlaceEdit.cpp:InPlaceEdit.cpp
# 	2:19:Application Include:VisWeb.h
# 	2:13:InPlaceEdit.h:InPlaceEdit.h
# End Section
# Section VisWeb : {15BD2C1E-F920-4320-9601-62F212EE8D60}
# 	2:16:CLASS: CFileMove:CFileMove
# 	2:12:FileMove.cpp:FileMove1.cpp
# 	2:10:FileMove.h:FileMove1.h
# 	2:19:Application Include:VisWeb.h
# End Section
# Section VisWeb : {57763EDB-F659-4FBB-9617-D2E29474C3F3}
# 	2:20:CLASS: CServerSocket:CServerSocket
# 	2:16:ServerSocket.cpp:ServerSocket.cpp
# 	2:19:Application Include:VisWeb.h
# 	2:14:ServerSocket.h:ServerSocket.h
# End Section
# Section VisWeb : {8BE77FE9-5C9B-4FE8-A2AA-D32D34862FC1}
# 	2:13:CLASS: CChain:CChain
# 	2:8:Fchain.h:Fchain.h
# 	2:19:Application Include:VisWeb.h
# 	2:10:Fchain.cpp:Fchain.cpp
# End Section
# Section VisWeb : {E04A5DA1-9A7E-4E14-AD38-F517CE924C07}
# 	2:18:GridDropTarget.cpp:GridDropTarget.cpp
# 	2:16:GridDropTarget.h:GridDropTarget.h
# 	2:22:CLASS: CGridDropTarget:CGridDropTarget
# 	2:19:Application Include:VisWeb.h
# End Section
# Section VisWeb : {70C56A44-67C5-4A14-81C3-4A3A6BF79E90}
# 	2:9:Image.cpp:Image.cpp
# 	2:7:Image.h:Image.h
# 	2:19:Application Include:VisWeb.h
# 	2:13:CLASS: CImage:CImage
# End Section
# Section VisWeb : {D2CE5BEE-6D76-4DB4-9A86-C2CA08486D19}
# 	2:13:InPlaceList.h:InPlaceList.h
# 	2:19:CLASS: CInPlaceList:CInPlaceList
# 	2:19:Application Include:VisWeb.h
# 	2:15:InPlaceList.cpp:InPlaceList.cpp
# End Section
# Section VisWeb : {289910AF-955C-45F2-BCC5-26C4791E7633}
# 	2:12:GridCtrl.cpp:GridCtrl.cpp
# 	2:10:GridCtrl.h:GridCtrl.h
# 	2:16:CLASS: CGridCtrl:CGridCtrl
# 	2:16:TYPEDEF: GV_ITEM:GV_ITEM
# 	2:15:CLASS: _GV_ITEM:_GV_ITEM
# 	2:17:TYPEDEF: GRID_ROW:GRID_ROW
# 	2:16:CLASS: CGridCell:CGridCell
# 	2:19:Application Include:VisWeb.h
# End Section
