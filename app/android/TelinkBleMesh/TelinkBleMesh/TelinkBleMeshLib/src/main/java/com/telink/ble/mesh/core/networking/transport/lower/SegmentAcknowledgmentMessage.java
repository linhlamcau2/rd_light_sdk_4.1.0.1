/********************************************************************************************************
 * @file SegmentAcknowledgmentMessage.java
 *
 * @brief for TLSR chips
 *
 * @author telink
 * @date Sep. 30, 2017
 *
 * @par Copyright (c) 2017, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/
package com.telink.ble.mesh.core.networking.transport.lower;

import com.telink.ble.mesh.core.MeshUtils;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * This class represents a Segment Acknowledgment Message, which is a type of Unsegmented Control Message PDU.
 * It contains the necessary fields and methods to parse and generate the byte array representation of the message.
 */
public class SegmentAcknowledgmentMessage extends UnsegmentedControlMessagePDU {
    public static final int DATA_LEN = 7;

    /**
     * 1 bit
     */
    private final int seg = 0;

    /**
     * 7 bits
     */
    private final int opcode = 0x00;

    /**
     * The OBO field shall be set to 0 by a node that is directly addressed by the received message
     * and shall be set to 1 by a Friend node that is acknowledging this message on behalf of a Low Power node.
     * <p>
     * As provisioner, obo is always 0
     * 1 bit
     */
    private final int obo = 0;

    /**
     * SeqZero of the Upper Transport PDU
     */
    private int seqZero;

    private final int rfu = 0;

    /**
     * Block acknowledgment for segments
     * 32 bits
     * If bit n is set to 0, then segment n is not being acknowledged.
     * Any bits for segments larger than SegN shall be set to 0 and ignored upon receipt.
     */
    private int blockAck = 0;

    /**
     * Parses the byte array representation of the message and populates the fields accordingly.
     * Returns true if the parsing is successful, false otherwise.
     *
     * @param lowerTransportData The byte array representation of the message
     * @return True if parsing is successful, false otherwise
     */
    public boolean parse(byte[] lowerTransportData) {
        if (lowerTransportData.length != DATA_LEN) return false;
//        int seqZero = ((lowerTransportData[1] & 0x7F) << 6) | ((lowerTransportData[2] & 0xFF) >> 2);
        int seqZero = MeshUtils.bytes2Integer(new byte[]{lowerTransportData[1], lowerTransportData[2]}
                , ByteOrder.BIG_ENDIAN);
        seqZero = (seqZero & 0x7FFF) >> 2;
        this.seqZero = seqZero;
        this.blockAck = MeshUtils.bytes2Integer(new byte[]{
                lowerTransportData[3],
                lowerTransportData[4],
                lowerTransportData[5],
                lowerTransportData[6],
        }, ByteOrder.BIG_ENDIAN);
        return true;
    }

    /**
     * Default constructor for SegmentAcknowledgmentMessage.
     */
    public SegmentAcknowledgmentMessage() {
    }

    /**
     * Constructor for SegmentAcknowledgmentMessage.
     *
     * @param seqZero  The SeqZero of the Upper Transport PDU
     * @param blockAck The block acknowledgment for segments
     */
    public SegmentAcknowledgmentMessage(int seqZero, int blockAck) {
        this.seqZero = seqZero;
        this.blockAck = blockAck;
    }

    /**
     * Converts the message to its byte array representation.
     *
     * @return The byte array representation of the message
     */
    @Override
    public byte[] toByteArray() {
        return ByteBuffer.allocate(DATA_LEN).order(ByteOrder.BIG_ENDIAN)
                .put((byte) ((seg << 7) | opcode))
                .put((byte) ((obo << 7) | ((seqZero >> 6) & 0x7F)))
                .put((byte) (((seqZero << 2) & 0xFC) | rfu))
                .putInt(blockAck).array();

    }

    /**
     * Returns a string representation of the SegmentAcknowledgmentMessage object.
     *
     * @return A string representation of the object
     */
    @Override
    public String toString() {
        return "SegmentAcknowledgmentMessage{" +
                "seg=" + seg +
                ", opcode=" + opcode +
                ", obo=" + obo +
                ", seqZero=" + seqZero +
                ", rfu=" + rfu +
                ", blockAck=" + blockAck +
                '}';
    }

    /**
     * Returns the SeqZero of the Upper Transport PDU.
     *
     * @return The SeqZero value
     */
    public int getSeqZero() {
        return seqZero;
    }

    /**
     * Returns the block acknowledgment for segments.
     *
     * @return The block acknowledgment value
     */
    public int getBlockAck() {
        return blockAck;
    }
}
