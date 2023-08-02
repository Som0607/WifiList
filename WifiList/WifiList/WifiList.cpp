// #pragma comment(lib, "wlanapi.lib")
// #include <stdio.h>
// #include <windows.h>
// #include <wlanapi.h>

// UINT8 bWait = 1;

// VOID WlanNotification(WLAN_NOTIFICATION_DATA* wlanNotifData, VOID* p)
// {
// 	if (wlanNotifData->NotificationCode == wlan_notification_acm_scan_complete)
// 	{
// 		bWait = false;
// 	}
// 	else if (wlanNotifData->NotificationCode == wlan_notification_acm_scan_fail)
// 	{
// 		printf("Scanning failed with error: %p\n", wlanNotifData->pData);
// 		bWait = false;
// 	}
// }

// //bool IsVistaOrHigher()
// //{
// // OSVERSIONINFO osVersion; ZeroMemory(&osVersion, sizeof(OSVERSIONINFO));
// // osVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
// //
// // if (!GetVersionEx(&osVersion))
// // return false;
// //
// // if (osVersion.dwMajorVersion >= 6)
// // return true;
// // return false;
// //}


// //trying to print beacon or probe resp IE RAW data
// DWORD FuncWlanBeaconFrame(PWLAN_BSS_ENTRY pWlanBssEntry, PBYTE pBeaconframe)
// {

// 	PBYTE pBlob = NULL;
// 	ULONG i = 0;

// 	printf("######## FuncWlanBeaconFrame--->######## \n \n");
// 	printf("offset of IE data blob =%d \n", pWlanBssEntry->ulIeOffset);
// 	printf("Size of IE data blob =%d \n", pWlanBssEntry->ulIeSize);
// 	printf("MAC ADRESS for AP  %02x:%02x:%02x:%02x:%02x:%02x\n", pWlanBssEntry->dot11Bssid[0],
// 		pWlanBssEntry->dot11Bssid[1],
// 		pWlanBssEntry->dot11Bssid[2],
// 		pWlanBssEntry->dot11Bssid[3],
// 		pWlanBssEntry->dot11Bssid[4],
// 		pWlanBssEntry->dot11Bssid[5]);
// 	printf("BSS Type %d \n ", pWlanBssEntry->dot11BssType);
// 	printf("SSID %s \n ", pWlanBssEntry->dot11Ssid.ucSSID);
// 	printf("Capability of beacon %d  \n \n ", pWlanBssEntry->usCapabilityInformation);
// 	//moving pointer the correct offset
// 	pBlob = (PBYTE)(pWlanBssEntry)+pWlanBssEntry->ulIeOffset;
// 	//IE data size
// 	memcpy((void*)pBeaconframe, (void*)pBlob, pWlanBssEntry->ulIeSize);
// 	printf("*****Total IE data byte by byte Last Beacon and Probe Response****** \n");
// 	do
// 	{
// 		printf("%d\t", pBeaconframe[i]);
// 		i++;
// 		if ((i != 0) && (i % 10) == 0)
// 			printf("\n");

// 	} while (i < pWlanBssEntry->ulIeSize);
// 	printf("\n");
// 	printf("*****Total IE data byte by byte Last Beacon and Probe Response****** \n \n");
// 	//printf("\n \n");
// 	//FuncWlanParseIEs(&pBeaconframe[0], pWlanBssEntry->ulIeSize);

// 	printf("######## FuncWlanBeaconFrame <---########  \n \n");
// 	return 0;
// }

// void FuncWlanGetNWList(GUID guidInterface, HANDLE phClientHandle, PWLAN_BSS_LIST pWlanBssList)
// {


// 	printf("######## FuncWlanGetNWList--->######## \n\n");
// 	DWORD hResult = WlanGetNetworkBssList(phClientHandle,
// 		&guidInterface,
// 		NULL,
// 		dot11_BSS_type_any,
// 		NULL,
// 		NULL,
// 		&pWlanBssList);

// 	if (hResult != ERROR_SUCCESS)
// 	{
// 		printf("Failed WlanGetNetworkBssList  %d \n ", hResult);
// 		printf("########FuncWlanGetBSSList<---######## \n \n");
// 		return;
// 	}
// 	printf("no of memebers in bss list entry=%d  \n ", pWlanBssList->dwNumberOfItems);
// 	printf("total size of the structure =%d  \n", pWlanBssList->dwTotalSize);

// 	if (pWlanBssList->dwNumberOfItems == 0)
// 	{
// 		printf("########FuncWlanGetBSSList is empty<---######## \n \n");
// 		return;
// 	}

// 	for (unsigned int i = 0; i < pWlanBssList->dwNumberOfItems; i++)
// 	{

// 		//PWLAN_BSS_ENTRY pWlanBssEntry = &pWlanBssList->wlanBssEntries[i];
// 		/*void* beaconframe = malloc(pWlanBssEntry->ulIeSize);
// 		FuncWlanBeaconFrame(pWlanBssEntry, (PBYTE)beaconframe);*/
// 		printf("\n\n********\n\nSSID: %s\n", pWlanBssList->wlanBssEntries[i].dot11Ssid.ucSSID);
// 		printf("SSID Length: %d\n", pWlanBssList->wlanBssEntries[i].dot11Ssid.uSSIDLength);
// 		printf("RegDomain %d\n", pWlanBssList->wlanBssEntries[i].bInRegDomain);
// 		printf("PhyType: %d\n", pWlanBssList->wlanBssEntries[i].dot11BssPhyType);
// 		printf("BSStype: %d\n", pWlanBssList->wlanBssEntries[i].dot11BssType);
// 		printf("RSSI: %d\n", pWlanBssList->wlanBssEntries[i].lRssi);
// 		printf("Centre Freq: %d\n", pWlanBssList->wlanBssEntries[i].ulChCenterFrequency);
// 		printf("Offset: %d\n", pWlanBssList->wlanBssEntries[i].ulIeOffset);
// 		printf("ulIE Size: %d\n", pWlanBssList->wlanBssEntries[i].ulIeSize);
// 		printf("L.Quality: %d\n", pWlanBssList->wlanBssEntries[i].uLinkQuality);
// 		printf("nPhy ID: %d\n", pWlanBssList->wlanBssEntries[i].uPhyId);
// 		printf("Beacon Period %d\n", pWlanBssList->wlanBssEntries[i].usBeaconPeriod);
// 		printf("nCap Info %d\n", pWlanBssList->wlanBssEntries[i].usCapabilityInformation);
// 		printf("Rate set %d\n*******\n\n", pWlanBssList->wlanBssEntries[i].wlanRateSet);


// 		printf("######## FuncWlanGetNWList<--- ######## \n \n");
// 	}
// }
// int main(int argc, char* argv[])
// {
// 	HANDLE hWlan = NULL;
// 	PWLAN_BSS_LIST pWlanBssList = NULL;

// 	DWORD dwError = 0;
// 	DWORD dwSupportedVersion = 0;
// 	DWORD dwClientVersion = 2;// = (IsVistaOrHigher() ? 2 : 1);

// 	GUID guidInterface; ZeroMemory(&guidInterface, sizeof(GUID));

// 	WLAN_INTERFACE_INFO_LIST* wlanInterfaceList = (WLAN_INTERFACE_INFO_LIST*)WlanAllocateMemory(sizeof(WLAN_INTERFACE_INFO_LIST));
// 	ZeroMemory(wlanInterfaceList, sizeof(WLAN_INTERFACE_INFO_LIST));

// 	WLAN_AVAILABLE_NETWORK_LIST* wlanNetworkList = (WLAN_AVAILABLE_NETWORK_LIST*)WlanAllocateMemory(sizeof(WLAN_AVAILABLE_NETWORK_LIST));
// 	ZeroMemory(wlanNetworkList, sizeof(WLAN_AVAILABLE_NETWORK_LIST));

// 	try
// 	{
// 		if (dwError = WlanOpenHandle(dwClientVersion, NULL, &dwSupportedVersion, &hWlan) != ERROR_SUCCESS)
// 			throw("[x] Unable access wireless interface");

// 		if (dwError = WlanEnumInterfaces(hWlan, NULL, &wlanInterfaceList) != ERROR_SUCCESS)
// 			throw("[x] Unable to enum wireless interfaces");

// 		wprintf(L"[!] Found adapter %s\n", wlanInterfaceList->InterfaceInfo[0].strInterfaceDescription);

// 		if (dwError = wlanInterfaceList->InterfaceInfo[0].isState != wlan_interface_state_not_ready)
// 		{
// 			if (wlanInterfaceList->dwNumberOfItems > 1)
// 			{
// 				// TODO: Add processing for multiple wireless cards here
// 				printf("[!] Detected multiple wireless adapters, using default\n");
// 				guidInterface = wlanInterfaceList->InterfaceInfo[0].InterfaceGuid;
// 			}
// 			else
// 			{
// 				guidInterface = wlanInterfaceList->InterfaceInfo[0].InterfaceGuid;
// 			}
// 		}
// 		else
// 			throw("[x] Default wireless adapter disabled");

// 		DWORD dwPrevNotif = 0;

// 		// Scan takes awhile so we need to register a callback
// 		if (dwError = WlanRegisterNotification(hWlan, WLAN_NOTIFICATION_SOURCE_ACM, TRUE,
// 			(WLAN_NOTIFICATION_CALLBACK)WlanNotification, NULL, NULL, &dwPrevNotif) != ERROR_SUCCESS)
// 			throw("[x] Unable to register for notifications");

// 		printf("[i] Scanning for nearby networks...\n");
// 		if (dwError = WlanScan(hWlan, &guidInterface, NULL, NULL, NULL) != ERROR_SUCCESS)
// 			throw("[x] Scan failed, check adapter is enabled");

// 		// Yawn...
// 		while (bWait)
// 			Sleep(100);

// 		// Unregister callback, don't care if it succeeds or not
// 		WlanRegisterNotification(hWlan, WLAN_NOTIFICATION_SOURCE_NONE, TRUE, NULL, NULL, NULL, &dwPrevNotif);

// 		if (dwError = WlanGetAvailableNetworkList(hWlan, &guidInterface, NULL, NULL, &wlanNetworkList) != ERROR_SUCCESS)
// 			throw("[x] Unable to obtain network list");

// 		printf("\nSSID\n: %d\n", wlanNetworkList->dwNumberOfItems);
// 		for (unsigned int i = 0; i < wlanNetworkList->dwNumberOfItems; i++)
// 		{
// 			printf("\nSSID:\t\t\t%s\nSIGNAL:\t\t\t%d%%\n",
// 				wlanNetworkList->Network[i].dot11Ssid.ucSSID,
// 				wlanNetworkList->Network[i].wlanSignalQuality);

// 			printf("SECURITY:\t\t");
// 			switch (wlanNetworkList->Network[i].dot11DefaultAuthAlgorithm)
// 			{
// 			case DOT11_AUTH_ALGO_80211_OPEN:
// 			case DOT11_AUTH_ALGO_80211_SHARED_KEY:
// 				printf("WEP");
// 				break;

// 			case DOT11_AUTH_ALGO_WPA:
// 			case DOT11_AUTH_ALGO_WPA_PSK:
// 			case DOT11_AUTH_ALGO_WPA_NONE:
// 				printf("WPA");
// 				break;

// 			case DOT11_AUTH_ALGO_RSNA:
// 			case DOT11_AUTH_ALGO_RSNA_PSK:
// 				printf("WPA2");
// 				break;

// 			default:
// 				printf("UNKNOWN");
// 				break;
// 			}
// 			printf("\n");
// 		}
// 	}
// 	catch (char* szError)
// 	{
// 		printf("%s \nQuitting...\n", szError);
// 	}

// 	printf("Sleeping\n");
// 	Sleep(1000);

// 	FuncWlanGetNWList(guidInterface, hWlan, pWlanBssList);
// 	if (wlanNetworkList)
// 		WlanFreeMemory(wlanNetworkList);
// 	if (wlanInterfaceList)
// 		WlanFreeMemory(wlanInterfaceList);
// 	if (hWlan)
// 		WlanCloseHandle(hWlan, NULL);


// 	return dwError;
// }

// // Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// // Debug program: F5 or Debug > Start Debugging menu

// // Tips for Getting Started:
// //   1. Use the Solution Explorer window to add/manage files
// //   2. Use the Team Explorer window to connect to source control
// //   3. Use the Output window to see build output and other messages
// //   4. Use the Error List window to view errors
// //   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
// //   6. In the future, to open this project again, go to File > Open > Project and select the .sln file