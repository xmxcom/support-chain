/**
*  @file
*  @copyright defined in xmax/LICENSE
*/
#pragma once

#include <block.hpp>

namespace Xmaxplatform {
namespace Chain {

	struct block_raw
	{
		uint32_t							block_num = 0;
		xmax_type_block_id					block_id;
		signed_block_header					new_header;
		vector<block_confirmation>			confirmations;
		builder_rule						verifiers;
		const xmax_type_block_id& prev_id() const
		{
			return new_header.previous;
		}

		void add_confirmation(const block_confirmation& conf, uint32_t skip);

		bool enough_confirmation() const;

	};

	struct block_pack : public block_raw
	{
		block_pack()
			: block(std::make_shared<signed_block>())
		{
		}

		signed_block_ptr	block;
	};

	using block_pack_ptr = std::shared_ptr<block_pack>;
}
}

FC_REFLECT(Xmaxplatform::Chain::block_raw, (block_id)(new_header))

FC_REFLECT_DERIVED(Xmaxplatform::Chain::block_pack, (Xmaxplatform::Chain::block_raw), (block))
