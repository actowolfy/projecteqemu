﻿//
// Copyright (C) 2001-2010 EQEMu Development Team (http://eqemulator.net). Distributed under GPL version 2.
//
// 
using System;
using System.IO;
using System.Collections.Generic;
using EQExtractor2.InternalTypes;
using EQExtractor2.OpCodes;
using EQPacket;
using MyUtils;

namespace EQExtractor2.Patches
{
    class PatchJuly132010Decoder : PatchMay122010Decoder
    {
        public PatchJuly132010Decoder()
        {
            Version = "EQ Client Build Date July 13 2010. (Including Test Server June 24 to July 8 2010).";

            ExpectedPPLength = 26640;
        }

        public override void RegisterExplorers()
        {
            base.RegisterExplorers();

            //OpManager.RegisterExplorer("OP_ZoneEntry", ExploreZoneEntry);
            //OpManager.RegisterExplorer("OP_CastSpell", ExploreCastSpell);
            //OpManager.RegisterExplorer("OP_SpawnAppearance", ExploreSpawnAppearance);
            //OpManager.RegisterExplorer("OP_ItemPacket", ExploreItemPacket);
        }

        public void ExploreItemPacket(StreamWriter OutputStream, ByteStream Buffer, PacketDirection Direction)
        {
            UInt32 StackSize = Buffer.ReadUInt32();
            Buffer.SkipBytes(4);
            UInt32 Slot = Buffer.ReadUInt32();
            UInt32 MerchantSlot = Buffer.ReadUInt32();
            UInt32 Price = Buffer.ReadUInt32();
            Int32 Quantity = Buffer.ReadInt32();
            Buffer.SetPosition(68);
            string Name = Buffer.ReadString(true);

            OutputStream.WriteLine("Item: {0} at Slot: {1}", Name, Slot);

        }
        

        public void ExploreCastSpell(StreamWriter OutputStream, ByteStream Buffer, PacketDirection Direction)
        {
            UInt32 Slot = Buffer.ReadUInt32();
            UInt32 SpellID = Buffer.ReadUInt32();

            OutputStream.WriteLine("Casting spell {0} from slot {1}", SpellID, Slot);

            OutputStream.WriteLine("");
        }
        public void ExploreMercenaryDataResponse(StreamWriter OutputStream, ByteStream Buffer, PacketDirection Direction)
        {
            UInt32 TypeCount = Buffer.ReadUInt32();

            //OutputStream.WriteLine("Type Count: {0}\r\n", TypeCount);
            OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Number of Types (Journeyman and Apprentice in this case\r\n", TypeCount);
            for (int i = 0; i < TypeCount; ++i)
            {
                UInt32 TypeDBStringID = Buffer.ReadUInt32();
                //OutputStream.WriteLine("  Type {0} DBStringID {1}", i, TypeDBStringID);
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // DBStringID for Type {1}", TypeDBStringID, i);
            }

            UInt32 Count2 = Buffer.ReadUInt32();

            //OutputStream.WriteLine("  Count 2 is {0}", Count2);
            OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Count of Sub-types that follow", Count2);

            for (int i = 0; i < Count2; ++i)
            {
                int Offset = Buffer.GetPosition();

                UInt32 Unknown1 = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Unknown", Unknown1);
                UInt32 DBStringID1 = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // DBStringID of Type", DBStringID1);
                UInt32 DBStringID2 = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // DBStringID of Sub-Type", DBStringID2);
                UInt32 PurchaseCost = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Purchase Cost", PurchaseCost);
                UInt32 UpkeepCost = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Upkeep Cost", UpkeepCost);
                UInt32 Unknown2 = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Unknown", Unknown2);
                UInt32 Unknown3 = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Unknown", Unknown3);
                UInt32 Unknown4 = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Unknown", Unknown4);

                byte Unknown5 = Buffer.ReadByte();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint8, Buffer, {0}); // Unknown", Unknown5);

                UInt32 Unknown6 = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Unknown", Unknown6);
                UInt32 Unknown7 = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Unknown", Unknown7);
                UInt32 Unknown8 = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Unknown", Unknown8);

                UInt32 StanceCount = Buffer.ReadUInt32();

                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Number of Stances for this Merc", StanceCount);

                UInt32 Unknown10 = Buffer.ReadUInt32();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Unknown", Unknown10);

                byte Unknown11 = Buffer.ReadByte();
                OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint8, Buffer, {0}); // Unknown", Unknown11);


                //OutputStream.WriteLine("   Offset: {5} Unknown1: {0} DBStrings: {1} {2} Purchase: {3} Upkeep: {4}\r\n", Unknown1, DBStringID1, DBStringID2,
                //                PurchaseCost, UpkeepCost, Offset);
                //OutputStream.WriteLine("   Unknowns: {0} {1} {2} {3} {4} {5} {6} {7} {8}\r\n",
                //                Unknown2, Unknown3, Unknown4, Unknown5, Unknown6, Unknown7, Unknown8, Unknown10, Unknown11);

                //OutputStream.WriteLine("    Stance Count: {0}", StanceCount);

                for (int j = 0; j < StanceCount; ++j)
                {
                    UInt32 StanceNum = Buffer.ReadUInt32();
                    OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Stance Number", StanceNum);
                    UInt32 StanceType = Buffer.ReadUInt32();
                    OutputStream.WriteLine("VARSTRUCT_ENCODE_TYPE(uint32, Buffer, {0}); // Stance DBStringID (1 = Passive, 2 = Balanced etc.", StanceType);

                    //OutputStream.WriteLine("     {0}: {1}", StanceNum, StanceType);
                }
                OutputStream.WriteLine("");
            }

            OutputStream.WriteLine("\r\nBuffer position at end is {0}", Buffer.GetPosition());
            OutputStream.WriteLine("");
        }
        
    }
}
