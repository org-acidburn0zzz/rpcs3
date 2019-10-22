#pragma once
#include "Utilities/types.h"
#include <vector>

namespace SPIRV
{
	enum class Opcode : u16
	{
		OpNop = 1,
		OpQuantizeToF16 = 116,
		OpFwidth = 209,
	};

	union instruction
	{
		u32 hex;

		struct
		{
			u16 opcode;
			u16 length;
		};
	};

	// Very basic instruction patching. The instructions have to be of compatible size and argument order at this time.
	void patch_instruction(std::vector<u32>& ucode, Opcode match, Opcode replace)
	{
		instruction inst;
		for (unsigned i = 5; i < ucode.size();)
		{
			inst.hex = ucode[i];

			if (inst.opcode == static_cast<u16>(match))
			{
				inst.opcode = static_cast<u16>(replace);
				ucode[i] = inst.hex;
			}

			i += inst.length;
		}
	}
}
