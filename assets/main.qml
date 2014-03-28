/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.system 1.0
import bb.cascades 1.0
import model.custom 1.0

Page {
    attachedObjects: [
        SystemToast {
            id: sysTst
        }
    ]
    Container {
        verticalAlignment: VerticalAlignment.Fill
        horizontalAlignment: HorizontalAlignment.Fill
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight
        }
        ListView {
            id: lstVwItems
            layoutProperties: StackLayoutProperties {
                spaceQuota: 10
            }
            dataModel: SqlDataModel {
                id: dtModel
                table: "test"
            }
            listItemComponents: [
                ListItemComponent {
                    StandardListItem {
                        title: ListItemData.name + " " + ListItemData.last_name
                        description: "Id: " + ListItemData.id
                    }
                }
            ]
            onCreationCompleted: {
                dtModel.load()
            }
        }
        Container {
            background: Color.LightGray
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            layoutProperties: StackLayoutProperties {
                spaceQuota: 0.1
            }
        }
        ScrollView {
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            layoutProperties: StackLayoutProperties {
                spaceQuota: 10
            }
            Container {
                topPadding: 20
                leftPadding: 20
                rightPadding: 20
                bottomPadding: 20
                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill
                Container {
                    topMargin: 20
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Label {
                        text: qsTr("Name") + ":" + Retranslate.onLocaleOrLanguageChanged
                        verticalAlignment: VerticalAlignment.Center
                    }
                    TextField {
                        id: txtFldName
                        hintText: ""
                        inputMode: TextFieldInputMode.EmailAddress
                    }
                }
                Container {
                    topMargin: 20
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Label {
                        text: qsTr("Last name") + ":" + Retranslate.onLocaleOrLanguageChanged
                        verticalAlignment: VerticalAlignment.Center
                    }
                    TextField {
                        id: txtFldLastName
                        hintText: ""
                        inputMode: TextFieldInputMode.EmailAddress
                    }
                }
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Button {
                        text: qsTr("Create item") + Retranslate.onLocaleOrLanguageChanged
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            var id = dtModel.create({
                                    "name": txtFldName.text,
                                    "last_name": txtFldLastName.text
                                })
                        }
                    }
                    Button {
                        text: qsTr("db Create item") + Retranslate.onLocaleOrLanguageChanged
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            var id = _db.create({
                                    "name": txtFldName.text,
                                    "last_name": txtFldLastName.text
                                })
                        }
                    }
                }
                Container {
                    topMargin: 20
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Label {
                        text: qsTr("Item") + ":" + Retranslate.onLocaleOrLanguageChanged
                        verticalAlignment: VerticalAlignment.Center
                    }
                    TextField {
                        id: txtFldItem
                        hintText: ""
                        inputMode: TextFieldInputMode.NumbersAndPunctuation
                    }
                }
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Button {
                        text: qsTr("Read item") + Retranslate.onLocaleOrLanguageChanged
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            var value = dtModel.read(parseInt(txtFldItem.text))
                            sysTst.body = "Id: " + value["id"] + "; Name: " + value["name"] + "; Last name: " + value["last_name"]
                            sysTst.show()
                        }
                    }
                    Button {
                        text: qsTr("db Read item") + Retranslate.onLocaleOrLanguageChanged
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            var value = _db.read(parseInt(txtFldItem.text))
                            sysTst.body = "Id: " + value["id"] + "; Name: " + value["name"] + "; Last name: " + value["last_name"]
                            sysTst.show()
                        }
                    }
                }
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Button {
                        text: qsTr("Remove item") + Retranslate.onLocaleOrLanguageChanged
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            dtModel.deleteRecordById(parseInt(txtFldItem.text))
                        }
                    }
                    Button {
                        text: qsTr("db Remove item") + Retranslate.onLocaleOrLanguageChanged
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            _db.deleteRecord(parseInt(txtFldItem.text))
                        }
                    }
                }
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Button {
                        text: qsTr("Update item") + Retranslate.onLocaleOrLanguageChanged
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            var value = {
                                "id": parseInt(txtFldItem.text),
                                "name": txtFldName.text,
                                "last_name": txtFldLastName.text
                            }
                            dtModel.update(value)
                        }
                    }
                    Button {
                        text: qsTr("db Update item") + Retranslate.onLocaleOrLanguageChanged
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            var value = {
                                "id": parseInt(txtFldItem.text),
                                "name": txtFldName.text,
                                "last_name": txtFldLastName.text
                            }
                            _db.update(value)
                        }
                    }
                }
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Button {
                        text: qsTr("Count") + Retranslate.onLocaleOrLanguageChanged
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            sysTst.body = dtModel.count()
                            sysTst.show()
                        }
                    }
                    Button {
                        text: qsTr("db Count") + Retranslate.onLocaleOrLanguageChanged
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            sysTst.body = _db.count()
                            sysTst.show()
                        }
                    }
                }
                Button {
                    text: qsTr("Clear") + Retranslate.onLocaleOrLanguageChanged
                    horizontalAlignment: HorizontalAlignment.Fill
                    onClicked: {
                        dtModel.clearRecords()
                    }
                }
            }
        }
    }
}