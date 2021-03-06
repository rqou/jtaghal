/***********************************************************************************************************************
*                                                                                                                      *
* ANTIKERNEL v0.1                                                                                                      *
*                                                                                                                      *
* Copyright (c) 2012-2016 Andrew D. Zonenberg                                                                          *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

/**
	@file
	@author Andrew D. Zonenberg
	@brief Implementation of RawBinaryFirmwareImage
 */
#include "jtaghal.h"

using namespace std;

/**
	@brief Initializes this object to empty
 */
RawBinaryFirmwareImage::RawBinaryFirmwareImage(string fname, string sdevname)
	: m_srcfname(fname)
{
	//Open the file and get size
	FILE* fp = fopen(fname.c_str(), "rb");
	if(!fp)
	{
		throw JtagExceptionWrapper(
			string("Failed to open firmware image ") + fname,
			"");
	}
	fseek(fp, 0, SEEK_END);
	raw_bitstream_len = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//Read it
	raw_bitstream = new unsigned char[raw_bitstream_len];
	fread(raw_bitstream, 1, raw_bitstream_len, fp);
	devname = sdevname;
	idcode = 0;

	fclose(fp);
}

/**
	@brief Free bitstream memory
 */
RawBinaryFirmwareImage::~RawBinaryFirmwareImage()
{
}

string RawBinaryFirmwareImage::GetDescription()
{
	char retval[1024];
	snprintf(retval, sizeof(retval), "firmware \"%s\" for device \"%s\"",
		m_srcfname.c_str(), devname.c_str());
	return retval;
}

