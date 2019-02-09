Message format in serial :
---------

All message are formated in COBS packets. On arduino, the lib
[PacketSerial](https://github.com/bakercp/PacketSerial) is used.


Format of packets :
---------

<table>
  <tr>
    <td>1</td>
    <td>2</td>
    <td>3</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>(...)</td>
    <td>n</td>
  </tr>
  <tr>
    <td colspan="2">CRC16 of the message</td>
    <td colspan="2">Message id (counter)</td>
    <td>Message type (see [message.h](../include/messages.h)</td>
    <td colspan="3">payload</td>
  </tr>
  <tr>
    <td colspan="2">2 bytes</td>
    <td colspan="2">2 bytes</td>
    <td>1 byte</td>
    <td colspan="3">...</td>
  </tr>
</table>
