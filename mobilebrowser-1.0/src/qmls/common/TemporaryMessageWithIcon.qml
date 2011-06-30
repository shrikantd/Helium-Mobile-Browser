/*--------------------------------------------------------
* Module Name : Helium Mobile Browser
* Version : 1.0
*
* Software Name : Helium Mobile Browser
* Version : 1.0
*
* Copyright (c) 2010 - 2011 France Telecom
* This software is distributed under the LGPL v2.1 license,
* the text of which is available at http://www.gnu.org/licenses/lgpl-2.1.html
* or see the "LICENSE.txt" file for more details.
*
*--------------------------------------------------------
* File Name   : TemporaryMessageWithIcon.qml
*
* Created     : 15 June 2011
*
*--------------------------------------------------------
* 1.0 - First open source release
*
*/

import Qt 4.7

BorderImage {
   id: temporaryMessageWithIcon

   property string title: ""
   property string subTitle: ""
   property string iconSource: ""

   function showAndDestroy() {
      seqAnim.start();
   }

   source: "qrc:/qmls/pics/tooltip-bg-100x100.png"
   border.top: 10
   border.bottom: 10
   border.left: 10
   border.right: 10

   width: 350; height: 70;
   anchors.centerIn: parent
   opacity: 0;
   z: 5

   //VHScrollDropShadow { anchors.fill: parent; anchors.margins: 4; z: -1 }

   Row {
       anchors.centerIn: parent
       spacing: 20
       Image {
           source: iconSource
           smooth: true; fillMode: Image.PreserveAspectFit;
           height: temporaryMessageWithIcon.height/2;
           width: height;
           //             anchors.left: parent.left;
           //             anchors.leftMargin: 10
           anchors.verticalCenter: parent.verticalCenter
           //anchors.margins: 20;
       }

       Column {
           anchors.left: iconSource.right;
           anchors.leftMargin: 10
           anchors.right: rowLayout.right;
           anchors.verticalCenter: parent.verticalCenter
           spacing: 5
           Text {
               id: titleLine;
               text: title;
               font.pixelSize: 20;
               font.bold: true;
               color: "#fff"; }
           Text {
               text: subTitle;
               font.pixelSize: 15;
               color: "#ccc";
               width: titleLine.paintedWidth;
               elide: Text.ElideRight;
           }
       }
   }

   SequentialAnimation {
      id: seqAnim
      PropertyAnimation { target: temporaryMessageWithIcon; property: "opacity"; duration: 300; to: 0.9; }
      PauseAnimation { duration: 1000; }
      PropertyAnimation { target: temporaryMessageWithIcon; property: "opacity"; duration: 300; to: 0; }
      ScriptAction { script: temporaryMessageWithIcon.destroy(); }
   }
}
