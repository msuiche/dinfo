/*++
    Offline Domain Join Metadata File Decoder

    Copyright (C) 2009 Matthieu Suiche (@msuiche)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

Module Name:

    - djoin.h

Abstract:

    - https://technet.microsoft.com/en-us/library/offline-domain-join-djoin-step-by-step(v=ws.10).aspx

Environment:

    - User mode

Revision History:

    - Matthieu Suiche

--*/


#define NETSETUP_PROVISION_DOWNLEVEL_PRIV_SUPPORT 0x1
#define NETSETUP_PROVISION_REUSE_ACCOUNT 0x2
#define NETSETUP_PROVISION_USE_DEFAULT_PASSWORD 0x4
#define NETSETUP_PROVISION_SKIP_ACCOUNT_SEARCH 0x8
#define NETSETUP_PROVISION_ONLINE_CALLER 0x40000000
#define NETSETUP_PROVISION_CHECK_PWD_ONLY 0x80000000

typedef struct _DOMAIN_DNS_POLICY { // sizeof = 0x2C
    TCHAR Name[4]; // 0x000
    TCHAR DnsDomainName[4]; // 0x008
    TCHAR DnsForestName[4]; // 0x010
    GUID DomainGuid; // 0x018
    PSID Sid; // 0x028
} DOMAIN_DNS_POLICY, *PDOMAIN_DNS_POLICY;

typedef struct _DOMAIN_CONTROLLER { // size of = 0x30
    PCHAR DomainControllerName; // 0x000
    PCHAR DomainControllerAddress; // 0x004
    ULONG DomainControllerAddressType; // 0x008
    GUID DomainGuid; // 0x00C
    PCHAR DomainName; // 0x01C
    PCHAR DnsForestName; // 0x020
    ULONG Flags; // 0x024
    PCHAR DcSiteName; // 0x28
    PCHAR ClientSiteName; // 0x2C
} DOMAIN_CONTROLLER, *PDOMAIN_CONTROLLER;

typedef struct _DOMAIN_INFORMATION {
    //
    // Global Information
    //
    LPVOID lpDomainName; // 0x008
    LPVOID lpMachineName; // 0x00C
    LPVOID lpMachinePassword; // 0x010

    //
    // Domain Policy
    //
    DOMAIN_DNS_POLICY DomainPolicy; // 0x014

    //
    // Domain Controller
    //
    DOMAIN_CONTROLLER DomainController; // 0x048

    //
    // Options - NETSETUP_PROVISION
    //
    ULONG Options; // 0x078

} DOMAIN_INFORMATION, *PDOMAIN_INFORMATION;

typedef struct _PROVISION_DATA {
    //
    // ODJ Blob
    //
    ULONG Version; // 0x000
    ULONG Size; // 0x004

    PDOMAIN_INFORMATION DomainInformation;

} PROVISION_DATA, *PPROVISION_DATA;