/*
 *  文件: common.js
 *  功能: 基础函数模块
 *  作者: 南野
 *  时间: 2015年7月21日
 */

// 判断是否为数字
function isNum(s) {
    if (s != null && s != "") {
        return !isNaN(s);
    }
    return false;
}

// 判断是否是字符串
function isString(s) {
    var ret = false;
    for (i = 0; i < s.length; i++) {
        if (parseInt(s.toLowerCase().charCodeAt(i)) >=97 &&
                parseInt(s.toLowerCase().charCodeAt(i)) <= 122) {
            ret = true;
        } else {
            ret = false;
            break;
        }
    }
    return ret
}

// 判断是否是含义
function isChinese(s) {
    var reg = /^[\u4e00-\u9fa5]+$/i;
    return reg.test(s);
}

// 判断是否是字母
function isAlphabet(s) {
    for(var i = 1; i < s.length; i++){
        if (s.charAt(i) < 'A' || s.charAt(i) >'Z') {
            if (s.charAt(i) < 'a' || s.charAt(i) > 'z') {
                return false;
            }
        }
    }
    return true;
}


/* 获取名字颜色根据名字首字母 */
function getColor(name) {

    /* 默认颜色 */
    var colorArr =  new Array("#ed6d00", "#ff8aa7", "#b48553", "#db9d31", "#c4da66",
                              "#22afd0", "#db4e2e", "#34cb3e", "#e5d647", "#21ade5",
                              "#a8ae28", "#f0b6c1", "#14b4a6", "#f4a98d", "#7dc163",
                              "#9c97c9", "#006980", "#de7063", "#ea617b", "#0b509e",
                              "#fabe00", "#b0cea5", "#cfdc29", "#7c509d", "#d33a81", "#508cc0");
    /* 26个字母 */
    var nameByte = new Array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
                             "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
                             "w", "x", "y", "z");
    if (JsCommon.isNum(name)) {
        console.log("是数字");
        return colorArr[name%26];
    }  else if (JsCommon.isChinese(name)) {
        console.log("是汉字");
        var lowerName = PinYin.pinyin.getCamelChars(name);
        var lastAph1 = lowerName.substr(lowerName.length - 1, 1);
        for (var i = 0; i < colorArr.length; i++) {
            if (lastAph1.toLowerCase() ===  nameByte[i]) {
                return colorArr[i];
            }
        }
    } else if (JsCommon.isAlphabet(name)) {
        console.log("是字母");
        var lastAph2 = name.substr(name.length - 1, 1);
        for (var i = 0; i < colorArr.length; i++) {
            if (lastAph2.toLowerCase() ===  nameByte[i]) {
                return colorArr[i];
            }
        }
    } else {
        console.log("是其他字符");
        return "#7c509d";
    }
}

function getFirstLetter(name) {

    var nameByte = new Array("a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
                             "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
                             "w", "x", "y", "z");

    var upperLetter = new Array("A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
                             "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
                             "W", "X", "Y", "Z");

    if (JsCommon.isChinese(name)) {
        var lowerName = PinYin.pinyin.getCamelChars(name);
        var lastAph1 = lowerName.substr(lowerName.length - 1, 1);
        for (var i = 0; i < nameByte.length; i++) {
            if (lastAph1.toLowerCase() ===  nameByte[i]) {
                return upperLetter[i];
            }
        }
    } else if (JsCommon.isAlphabet(name)) {
        var lastAph2 = name.substr(name.length - 1, 1);
        for (var i = 0; i < nameByte.length; i++) {
            if (lastAph2.toLowerCase() ===  nameByte[i]) {
                return upperLetter[i];
            }
        }
    } else {
        return "#";
    }
}

function getDateTime() {

    var date = new Date();
    var hour = date.getHours();			//小时
    var minute = date.getMinutes();		//分钟
    var second = date.getSeconds();		//秒钟

    //小时小于10时显示为'0X'
    if (hour < 10) {
        hour = "0" + hour;
    }

    //分钟小于10时显示为'0X'
    if (minute < 10) {
        minute = "0" + minute;
    }

    //秒钟小于10时显示为'0X'
    if (second < 10) {
        second = "0" + second;
    }
    var colon = ":";
    var dash = "-";
    var result = "";

    result += (hour + colon + minute);
    return result;
}

/* 计算聊天内容长度 */
function strlen(str) {
    var s = 0;
    for (var i = 0; i < str.length; i++) {
        if(str.charAt(i).match(/[u0391-uFFE5]/)) {
            s += 2;
        } else {
            s++;
        }
    }
    return s;
}


function getByteLen(val) {
    var len = 0;
    for (var i = 0; i < val.length; i++) {
        var a = val.charAt(i);
        if (a.match(/[^\x00-\xff]/ig) != null){
            len += 2;
        } else {
            len += 1;
        }
    }
    console.log("bytes - " + len);
    return len;
}


/* 计算聊天框的高度 */
function getMessageFrameHeight(height_size, user_data_width, max_row_width) {

    var total_bytes_width = user_data_width;
    var row_num = parseInt(total_bytes_width / max_row_width);

    if (row_num === 0) {
        row_num = 1;
        return row_num * height_size;
    }

    if ((total_bytes_width % 250 > 0) && row_num != 0) {
        row_num = row_num + 1;
    }
    return row_num * height_size;
}

function getMessageFrameWidth(total_width) {
    var width = total_width > 250 ? 250 : total_width;
    return width;
}










