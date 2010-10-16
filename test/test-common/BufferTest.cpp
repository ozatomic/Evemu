/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2008 The EVEmu Team
    For the latest information visit http://evemu.mmoforge.org
    ------------------------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any later
    version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place - Suite 330, Boston, MA 02111-1307, USA, or go to
    http://www.gnu.org/copyleft/lesser.txt.
    ------------------------------------------------------------------------------------
    Author:     Bloody.Rabbit
*/

#include "TestCommonPCH.h"

#include "BufferTest.h"

/*************************************************************************/
/* BufferTest                                                            */
/*************************************************************************/
const uint8 BufferTest::PLAIN_DATA[] =
{
    0xA8, 0xDA, 0x06, 0x84, 0x43, 0x69, 0xC8
};

CppUnit::TestSuite* BufferTest::suite()
{
    CppUnit::TestSuite* s = new CppUnit::TestSuite( "BufferTest" );

    s->addTest( new CppUnit::TestCaller< BufferTest> ( "BufferTest::testConstructorSize",
                                                       &BufferTest::testConstructorSize ) );
    s->addTest( new CppUnit::TestCaller< BufferTest> ( "BufferTest::testConstructorRange",
                                                       &BufferTest::testConstructorRange ) );
    s->addTest( new CppUnit::TestCaller< BufferTest> ( "BufferTest::testConstructorCopy",
                                                       &BufferTest::testConstructorCopy ) );

    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testOperatorAppend",
                                                       &BufferTest::testOperatorAppend ) );
    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testOperatorAssign",
                                                       &BufferTest::testOperatorAssign ) );
    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testOperatorCopy",
                                                       &BufferTest::testOperatorCopy ) );

    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testAppendValue",
                                                       &BufferTest::testAppendValue ) );
    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testAppendRange",
                                                       &BufferTest::testAppendRange ) );

    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testAssignValue",
                                                       &BufferTest::testAssignValue ) );
    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testAssignRange",
                                                       &BufferTest::testAssignRange ) );

    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testReserve",
                                                       &BufferTest::testReserve ) );
    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testReserveAt",
                                                       &BufferTest::testReserveAt ) );

    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testResize",
                                                       &BufferTest::testResize ) );
    s->addTest( new CppUnit::TestCaller< BufferTest >( "BufferTest::testResizeAt",
                                                       &BufferTest::testResizeAt ) );

    return s;
}

void BufferTest::setUp()
{
    mBuffer = new Util::Buffer;
}

void BufferTest::tearDown()
{
    SafeDelete( mBuffer );
}

void BufferTest::testConstructorSize()
{
    const size_t size = 8;
    const uint8 fill = PLAIN_DATA[ 5 ];

    SafeDelete( mBuffer );
    mBuffer = new Util::Buffer( size, fill );

    CPPUNIT_ASSERT_EQUAL( size * sizeof( uint8 ), mBuffer->size() );
    CPPUNIT_ASSERT_EQUAL( fill, mBuffer->Get< uint8 >( size - 1 ) );
}

void BufferTest::testConstructorRange()
{
    const uint32* begin = reinterpret_cast< const uint32* >( &PLAIN_DATA[ 0 ] );
    const uint32* end = reinterpret_cast< const uint32* >( &PLAIN_DATA[ 7 ] );

    SafeDelete( mBuffer );
    mBuffer = new Util::Buffer( begin, end );

    CPPUNIT_ASSERT_EQUAL( sizeof( uint32 ) * static_cast< size_t >( end - begin ),
                          mBuffer->size() );
    /*
     * The primary iterators must be the Buffer's ones here, because
     * the way pointer arithmetic works and the way std::equal is
     * implemented guarantee going out-of-bounds.
     */
    CPPUNIT_ASSERT( std::equal( mBuffer->begin< uint32 >(),
                                mBuffer->end< uint32 >(),
                                begin ) );
}

void BufferTest::testConstructorCopy()
{
    const Util::Buffer buf( &PLAIN_DATA[ 0 ], &PLAIN_DATA[ 7 ] );

    SafeDelete( mBuffer );
    mBuffer = new Util::Buffer( buf );

    CPPUNIT_ASSERT_EQUAL( buf.size(), mBuffer->size() );
    CPPUNIT_ASSERT( std::equal( buf.begin< uint8 >(), buf.end< uint8 >(),
                                mBuffer->begin< uint8 >() ) );
}

void BufferTest::testOperatorAppend()
{
    const Util::Buffer::ConstIterator< uint32 > itr = mBuffer->end< uint32 >();
    const uint32 val = reinterpret_cast< const uint32& >( PLAIN_DATA[ 1 ] );

    *mBuffer << val;

    CPPUNIT_ASSERT( mBuffer->end< uint32 >() == itr + 1 );
    CPPUNIT_ASSERT_EQUAL( val, *itr );
}

void BufferTest::testOperatorAssign()
{
    const uint32 val = reinterpret_cast< const uint32& >( PLAIN_DATA[ 3 ] );

    *mBuffer = val;

    CPPUNIT_ASSERT_EQUAL( sizeof( uint32 ), mBuffer->size() );
    CPPUNIT_ASSERT_EQUAL( val, mBuffer->Get< uint32 >( 0 ) );
}

void BufferTest::testOperatorCopy()
{
    const Util::Buffer buf( &PLAIN_DATA[ 0 ], &PLAIN_DATA[ 7 ] );

    *mBuffer = buf;

    CPPUNIT_ASSERT_EQUAL( buf.size(), mBuffer->size() );
    CPPUNIT_ASSERT( std::equal( buf.begin< uint8 >(), buf.end< uint8 >(),
                                mBuffer->begin< uint8 >() ) );
}

void BufferTest::testAppendValue()
{
    const Util::Buffer::ConstIterator< uint32 > itr = mBuffer->end< uint32 >();
    const uint32 val = reinterpret_cast< const uint32& >( PLAIN_DATA[ 2 ] );

    mBuffer->Append( val );

    CPPUNIT_ASSERT( mBuffer->end< uint32 >() == itr + 1 );
    CPPUNIT_ASSERT_EQUAL( val, *itr );
}

void BufferTest::testAppendRange()
{
    const Util::Buffer::Iterator< uint32 > itr = mBuffer->end< uint32 >();
    const uint32* begin = reinterpret_cast< const uint32* >( &PLAIN_DATA[ 0 ] );
    const uint32* end = reinterpret_cast< const uint32* >( &PLAIN_DATA[ 7 ] );

    mBuffer->Append( begin, end );

    CPPUNIT_ASSERT( mBuffer->end< uint32 >() == itr + ( end - begin ) );
    /*
     * The primary iterators must be the Buffer's ones here, because
     * the way pointer arithmetic works and the way std::equal is
     * implemented guarantee going out-of-bounds.
     */
    CPPUNIT_ASSERT( std::equal( itr, mBuffer->end< uint32 >(), begin ) );
}

void BufferTest::testAssignValue()
{
    const uint32 val = reinterpret_cast< const uint32& >( PLAIN_DATA[ 1 ] );

    mBuffer->Assign( val );

    CPPUNIT_ASSERT_EQUAL( sizeof( uint32 ), mBuffer->size() );
    CPPUNIT_ASSERT_EQUAL( val, mBuffer->Get< uint32 >( 0 ) );
}

void BufferTest::testAssignRange()
{
    const uint32* begin = reinterpret_cast< const uint32* >( &PLAIN_DATA[ 0 ] );
    const uint32* end = reinterpret_cast< const uint32* >( &PLAIN_DATA[ 7 ] );

    mBuffer->Assign( begin, end );
                     
    CPPUNIT_ASSERT_EQUAL( sizeof( uint32 ) * static_cast< size_t >( end - begin ),
                          mBuffer->size() );
    /*
     * The primary iterators must be the Buffer's ones here, because
     * the way pointer arithmetic works and the way std::equal is
     * implemented guarantee going out-of-bounds.
     */
    CPPUNIT_ASSERT( std::equal( mBuffer->begin< uint32 >(),
                                mBuffer->end< uint32 >(),
                                begin ) );
}

void BufferTest::testReserve()
{
    const size_t count = 4;

    mBuffer->Reserve< uint32 >( count );

    CPPUNIT_ASSERT( count * sizeof( uint32 ) <= mBuffer->capacity() );
}

void BufferTest::testReserveAt()
{
    mBuffer->Resize< uint32 >( 4 );
    const Util::Buffer::ConstIterator< uint32 > itr = mBuffer->begin< uint32 >() + 4;
    const size_t count = 4;

    mBuffer->ReserveAt< uint32 >( itr, count );

    CPPUNIT_ASSERT( ( count + 4 ) * sizeof( uint32 ) <= mBuffer->capacity() );
}

void BufferTest::testResize()
{
    mBuffer->Resize< uint32 >( 0 );
    const size_t size = 4;
    const uint32 fill = reinterpret_cast< const uint32& >( PLAIN_DATA[ 0 ] );

    mBuffer->Resize( size, fill );

    CPPUNIT_ASSERT_EQUAL( size * sizeof( uint32 ), mBuffer->size() );
    CPPUNIT_ASSERT_EQUAL( fill, mBuffer->Get< uint32 >( size - 1 ) );
}

void BufferTest::testResizeAt()
{
    mBuffer->Resize< uint32 >( 4 );
    const Util::Buffer::ConstIterator< uint32 > itr = mBuffer->begin< uint32 >() + 4;
    const size_t size = 4;
    const uint32 fill = reinterpret_cast< const uint32& >( PLAIN_DATA[ 1 ] );

    mBuffer->ResizeAt( itr, size, fill );

    CPPUNIT_ASSERT_EQUAL( ( size + 4 ) * sizeof( uint32 ), mBuffer->size() );
    CPPUNIT_ASSERT_EQUAL( fill, mBuffer->Get< uint32 >( size + 3 ) );
}