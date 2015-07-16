var imageFilter = "Images (*.jpg *.jpeg *.png *.bmp)"

function loadFromFile(context) {
    if (document.modified) {
        // todo
    }

    var file = util.openFileDialog("Choose image to edit", ".", imageFilter)
    if (file === "")
        return;
    document.source = file
}

function saveDocument() {
    console.debug("saveDocument()");
    if (!document.save(document.source)) {
        console.log("Can't save to " + document.source);
        return false;
    }
    return true;
}

function saveAsDocument() {
    console.debug("saveAsDocument()");
    var file = util.saveFileDialog("Save as...", ".", imageFilter);
    if (file === "")
        return false;
    if (!document.save(file)) {
        console.log("Can't save to " + document.source);
        return false;
    }
    return true;
}

function channelIconColor(channel) {
    if (channel == "value")
        return "gray";
    return channel;
}

function channelMaxColor(channel) {
    if (channel == "value")
        return "white";
    return channel;
}

function autoLevels(histogram) {
    ["red", "green", "blue"].forEach(function(channel) {
        var low = histogram.getLow(channel);
        var high = histogram.getHigh(channel)
        if (high - low > 10)
            document.adjustContrast(low, high, channel);
    });
}
