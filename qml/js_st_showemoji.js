

  var ST_EMOJI = [
    "1f601",
    "1f603",
    "1f600",
    "1f60a",
    "263a",
    "1f609",
    "1f60d",
    "1f618",
    "1f61a",
    "1f617",
    "1f619",
    "1f61c",
    "1f61d",
    "1f61b",
    "1f633",
    "1f62c",
    "1f614",
    "1f60c",
    "1f612",
    "1f61e",
    "1f623",
    "1f622",
    "1f602",
    "1f62d",
    "1f62a",
    "1f625",
    "1f630",
    "1f605",
    "1f613",
    "1f629",
    "1f62b",
    "1f628",
    "1f631",
    "1f620",
    "1f621",
    "1f624",
    "1f616",
    "1f606",
    "1f60b",
    "1f637",
    "1f60e",
    "1f634",
    "1f635",
    "1f632",
    "1f61f",
    "1f626",
    "1f627",
    "1f608",
    "1f47f",
    "1f62e",
    "1f601",
    "1f610",
    "1f615",
    "1f62f",
    "1f636",
    "1f607",
    "1f60f",
    "1f611",
    "1f472",
    "1f473",
    "1f46e",
    "1f477",
    "1f482",
    "1f476",
    "1f466",
    "1f467",
    "1f468",
    "1f469",
    "1f474",
    "1f475",
    "1f471",
    "1f47c",
    "1f478",
    "1f63a",
    "1f638",
    "1f63b",
    "1f63d",
    "1f63c",
    "1f640",
    "1f63f",
    "1f639",
    "1f63e",
    "1f479",
    "1f47a",
    "1f648",
    "1f649",
    "1f64a",
    "1f480",
    "1f47d",
    "1f4a9",
    "1f525",
    "2728",
    "1f31f",
    "1f4ab",
    "1f4a5",
    "1f4a2",
    "1f4a6",
    "1f4a7",
    "1f4a4",
    "1f4a8",
    "1f442",
    "1f440",
    "1f443",
    "1f445",
    "1f444",
    "1f44d",
    "1f44e",
    "1f44c",
    "1f44a",
    "270a",
    "270c",
    "1f44b",
    "270b",
    "1f450",
    "1f446",
    "1f447",
    "1f449",
    "1f448",
    "1f64c",
    "1f64f",
    "261d",
    "1f44f",
    "1f4aa",
    "1f6b6",
    "1f3c3",
    "1f483",
    "1f46b",
    "1f46a",
    "1f46c",
    "1f46d",
    "1f48f",
    "1f491",
    "1f46f",
    "1f646",
    "1f645",
    "1f481",
    "1f64b",
    "1f486",
    "1f487",
    "1f485",
    "1f470",
    "1f64e",
    "1f64d",
    "1f647",
    "1f3a9",
    "1f451",
    "1f452",
    "1f45f",
    "1f45e",
    "1f461",
    "1f460",
    "1f462",
    "1f455",
    "1f454",
    "1f45a",
    "1f457",
    "1f3bd",
    "1f456",
    "1f458",
    "1f459",
    "1f4bc",
    "1f45c",
    "1f45d",
    "1f45b",
    "1f453",
    "1f380",
    "1f302",
    "1f484",
    "1f49b",
    "1f499",
    "1f49c",
    "1f49a",
    "2764",
    "1f494",
    "1f497",
    "1f493",
    "1f495",
    "1f496",
    "1f49e",
    "1f498",
    "1f48c",
    "1f48b",
    "1f48d",
    "1f48e",
    "1f464",
    "1f465",
    "1f4ac",
    "1f463",
    "1f4ad" ];
function getEmojiModel(position) {
    //总共6页，一页35个，每行7个
    var elen=ST_EMOJI.length;
    var pagecount=48;
    var pagenum=12;
    var endrow=Math.ceil(elen/pagecount);
    var ecount=position*pagecount;
    var efrom=ecount-pagecount;
    var eend=ecount;
    if (position==endrow){
        eend=189;
        efrom=145;
    }    

    var str="";
    var fnum=0;
    var i=1;
    var fname="imgc";
    var em="";
    var emarry="";

    for (var k=efrom;k<=eend;k++) {
      em = ST_EMOJI[k];      
      fnum=i%pagenum;


      if (i%pagenum==0 )
      {
          fnum=pagenum;
      }
      fname="imgc"+fnum;      
      //console.log("k values is "+k+"____em value :"+em);
      em=fname+" : "+"\"qrc:/img/emoji/"+em+".png\"";
      //console.log(em);
      if (em=="" || em==null){
          continue;
      }

      if (fnum==1){
        str="{"+em;
      }
       else{
          if (fnum==pagenum){
           str=str+","+em+"}"

          } else{
             if (str==""){
              str=em;
             } else
            str=str+","+em;
          }
      }

      if (fnum==pagenum){
          if(emarry==""){
              emarry=str;
          } else
          {
            emarry=emarry+","+str;
          }
      }
        i=i+1;
    }
    return "["+emarry+"]";
}






