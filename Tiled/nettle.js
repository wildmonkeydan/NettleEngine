let componentEditor = tiled.registerAction("EditComponents", function(action){
    var components = [];
    const jsonFile = new TextFile("C:\\Users\\dantu\\Documents\\components.json", TextFile.ReadWrite);
    const jsonStr = jsonFile.readAll();
    components = JSON.parse(jsonStr);
    

    let dialog = new Dialog("Edit Components");
    dialog.addLabel("Add or remove components to use in this project");
    dialog.addNewRow();
    let addButton = dialog.addButton("Add");
    let okButton = dialog.addButton("OK");
    let cancelButton = dialog.addButton("Cancel");

    var componentElems = [];
    for(var i = 0; i < components.length; i++){
        dialog.addNewRow(); 
        componentElems.push(dialog.addTextInput("Component:", ""));
        componentElems[i].text = components[i];
    }
    cancelButton.clicked.connect(function() {dialog.reject()});
    okButton.clicked.connect(function() {dialog.accept()});
    addButton.clicked.connect(function() {
        dialog.addNewRow(); 
        componentElems.push(dialog.addTextInput("Component:", ""));});

    dialog.finished.connect(function(result) {
        if(result == Dialog.Rejected){
            return;
        }
        else {
            for(var i = 0; i < componentElems.length; i++){
                components[i] = componentElems[i].text;
            }
        }
        jsonFile.truncate();
        jsonFile.write(JSON.stringify(components));
        jsonFile.close();
    });   
        
    dialog.show();
    
});
componentEditor.text = "Edit Components";

tiled.extendMenu("Edit", [{ action: "EditComponents" }, { separator: true }]);