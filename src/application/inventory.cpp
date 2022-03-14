#include "pch.h"
#include "../interface/interface.h"
#include "inventory.h"

Inventory::Inventory() = default;
Inventory::~Inventory() = default;

void Inventory::Load( const std::string& path )
{
	std::ifstream stream( path );
	std::string fileData( ( std::istreambuf_iterator<char>( stream ) ), std::istreambuf_iterator<char>() );

	Json::Document document;
	document.Parse( fileData.c_str() );
	assert( !document.HasParseError() );

	assert( document.IsObject() );

	// name
	assert( document.HasMember( "name" ) );
	assert( document[ "name" ].IsString() );
	m_ownerName = document[ "name" ].GetString();

	// maxSpace
	assert( document.HasMember( "maxSpace" ) );
	assert( document[ "maxSpace" ].IsInt() );
	m_maxSpace = document[ "maxSpace" ].GetInt();

	// currentMoney
	assert( document.HasMember( "currentMoney" ) );
	assert( document[ "currentMoney" ].IsInt() );
	m_currentMoney = document[ "currentMoney" ].GetInt();

	// items
	assert( document.HasMember( "items" ) );
	const Json::Value& arrayObject = document[ "items" ];
	assert( arrayObject.IsArray() );
	for( Json::SizeType i = 0; i < arrayObject.Size(); i++ )
	{
		Item newItem;

		// name
		assert( arrayObject[i].HasMember( "name" ) );
		assert( arrayObject[ i ][ "name" ].IsString() );
		newItem.m_name = arrayObject[ i ][ "name" ].GetString();

		// cost
		assert( arrayObject[ i ].HasMember( "cost" ) );
		assert( arrayObject[ i ][ "cost" ].IsInt() );
		newItem.m_cost = arrayObject[ i ][ "cost" ].GetInt();
		
		// size
		assert( arrayObject[ i ].HasMember( "size" ) );
		assert( arrayObject[ i ][ "size" ].IsInt() );
		newItem.m_size = arrayObject[ i ][ "size" ].GetInt();

		// rarity
		assert( arrayObject[ i ].HasMember( "rarity" ) );
		assert( arrayObject[ i ][ "rarity" ].IsInt() );
		int rarity = arrayObject[ i ][ "rarity" ].GetInt();
		assert( rarity < static_cast< int >( RarityLevel::MAX ) );
		newItem.m_rarity = static_cast< RarityLevel >( rarity );

		// count
		assert( arrayObject[ i ].HasMember( "count" ) );
		assert( arrayObject[ i ][ "count" ].IsInt() );
		newItem.m_count = arrayObject[ i ][ "count" ].GetInt();

		// items
		assert( arrayObject[ i ].HasMember( "attributes" ) );
		const Json::Value& internalArrayObject = arrayObject[ i ][ "attributes" ];
		assert( internalArrayObject.IsArray() );
		for( Json::SizeType i = 0; i < internalArrayObject.Size(); i++ )
		{
			assert( internalArrayObject[ i ].IsString() );
			newItem.m_attributes.push_back( internalArrayObject[ i ].GetString() );
		}

		m_items.push_back( std::move( newItem ) );
	}
}
