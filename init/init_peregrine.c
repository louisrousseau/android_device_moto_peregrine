/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm.h"

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char radio[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
//  char cdma_variant[92];
//  FILE *fp;
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.boot.radio", radio);
    // falcon had falcon_1.img.gz, falcon_3.img.gz and falcon_6.img.gz for "Global", CDMA and AWS respectively, peregrine doesn't quite match this
    // I'll comment out the CDMA stuff for now since there hasn't been anything released, but the /fsg partition has mention of Verizon and Sprint
    /*    
    fp = popen("/system/bin/ls -la /fsg/peregrine_3.img.gz | /system/xbin/cut -d '_' -f3", "r");
    fgets(cdma_variant, sizeof(cdma_variant), fp);
    pclose(fp);
    */
    if (ISMATCH(radio, "0x1")) {
        // XT1045
        property_set("ro.product.device", "peregrine");
        property_set("ro.product.model", "Moto G LTE");
        property_set("ro.build.description", "peregrine_retus-user 4.4.3 KXB21.14-L1.23-4 1 release-keys");
        property_set("ro.build.fingerprint", "motorola/peregrine_retus/peregrine:4.4.3/KXB21.14-L1.23-4/1:user/release-keys");
        property_set("ro.mot.build.customerid", "retus");
        property_set("persist.radio.multisim.config", "");
    } /* else if (ISMATCH(radio, "0x3")) {
        // CDMA
        ERROR("CDMA variant=%s", cdma_variant);
        if (ISMATCH(cdma_variant, "verizon")) {
            // xt1028
            property_set("ro.product.device", "falcon_cdma");
            property_set("ro.product.model", "Moto G");
            property_set("ro.build.description", "falcon_verizon-user 4.3 14.10.0Q3.X-84-14 16 release-keys");
            property_set("ro.build.fingerprint", "motorola/falcon_verizon/falcon_cdma:4.3/14.10.0Q3.X-84-14/16:user/release-keys");
            property_set("persist.radio.multisim.config", "");
            property_set("ro.mot.build.customerid", "verizon");
            property_set("ro.cdma.home.operator.alpha", "Verizon");
            property_set("ro.cdma.home.operator.numeric", "310004");
            property_set("ro.com.google.clientidbase.ms", "android-verizon");
            property_set("ro.com.google.clientidbase.am", "android-verizon");
            property_set("ro.com.google.clientidbase.yt", "android-verizon");
	    } else if (ISMATCH(cdma_variant, "sprint")) {
			// xt1031
            property_set("ro.product.device", "falcon_cdma");
            property_set("ro.product.model", "Moto G");
            property_set("ro.build.description", "falcon_sprint-user 4.3 14.10.0Q3.X-84-14 16 release-keys");
            property_set("ro.build.fingerprint", "motorola/falcon_sprint/falcon_cdma:4.3/14.10.0Q3.X-84-14/16:user/release-keys");
            property_set("persist.radio.multisim.config", "");
            property_set("ro.mot.build.customerid", "sprint");
        }

        property_set("ro.telephony.default_network", "9");
        property_set("ro.telephony.gsm-routes-us-smsc", "");
        property_set("persist.radio.vrte_logic", "");
        property_set("persist.radio.0x9e_not_callname", "");
        property_set("persist.radio.skip_data_check", "");
        property_set("persist.ril.max.crit.qmi.fails", "");
        property_set("ro.cdma.home.operator.isnan", "");
        property_set("ro.cdma.otaspnumschema", "");
        property_set("ro.cdma.data_retry_config", "");
        property_set("ro.gsm.data_retry_config", "");

    } */

    /* To be completed with sections for the: 
     * XT1039 (Europe)
     * XT1040 (Brasil) 
     * and other HSPA/LTE variants that might appear
     * 
     * Leaving XT1034 as reference
     */

/*    else if (ISMATCH(radio, "0x6")) {
        // XT1034
        property_set("ro.product.device", "falcon_umts");
        property_set("ro.product.model", "Moto G");
        property_set("ro.build.description", "falcon_retuaws-user 4.4.2 KXB20.9-1.8-1.4 4 release-keys");
        property_set("ro.build.fingerprint", "motorola/falcon_retuaws/falcon_umts:4.4.2/KXB20.9-1.8-1.4/4:user/release-keys");
        property_set("ro.mot.build.customerid", "retusa_aws");
        property_set("persist.radio.multisim.config", "");
    } */
    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    ERROR("Found radio id %s setting build properties for %s device\n", radio, devicename);
}
