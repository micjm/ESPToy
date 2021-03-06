const char html_home[] PROGMEM = R"(<head>
<title>ESPToy Demo</title>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<meta charset=utf-8 />
<style>
.colour-changer {
width: 10px;
height: 10px;
}
.disp-value {
width: 50px;
}
table {
border: 0px;
padding: 0px;
border-spacing:0;
border-collapse: collapse;
}
</style>
</head>
<body>
<table>
<tr>
<td><b>Analog:</b></td>
<td class='disp-value'><label id='lbl_adc'></label></td>
<td><b>Button</b>:</td>
<td class='disp-value'><label id='lbl_but'></label></td>
</tr>   
<tr>
</table>
<p>Click on a color below:</p>
<script>
var nh=36,nl=25;
function w(s) {document.write(s);}
function id(s){return document.getElementById(s);}
w('<table>');
for(i=0;i<nh;i++) {
w('<tr>');
for(j=0;j<nl;j++) {
w('<td class=colour-changer></td>');
}
w('</tr>');
}
w('</table>');
function toArray(arr) {
return Array.prototype.slice.call(arr);
}
function rgb2cc(rgb) {
rgb = rgb.match(/^rgba?\((\d+),\s*(\d+),\s*(\d+)(?:,\s*(\d+))?\)$/);
var r=(Math.pow(rgb[1]/255.0,1.8)*255>>0)*4;
var g=(Math.pow(rgb[2]/255.0,1.8)*255>>0)*4;
var b=(Math.pow(rgb[3]/255.0,1.8)*255>>0)*4;
return 'cc?r='+r+'&g='+g+'&b='+b;
}
toArray(document.querySelectorAll('.colour-changer')).forEach(function(div, i, arr) {
var ih=(i/nl)>>0;
var il=i%nl;
var hue=(ih/nh)*360;
var bright=100-(il+1)/nl*100;
div.style.background='hsl('+hue+',100%,'+bright+'%)';
function click(event) {
var xhr = new XMLHttpRequest();
xhr.open('GET', rgb2cc(div.style.backgroundColor), true);
xhr.send(null);
event.preventDefault();
} 
div.addEventListener('click', click);      
});
function loadValues() {
var xhr=new XMLHttpRequest();
xhr.onreadystatechange=function() {
if(xhr.readyState==4 && xhr.status==200) {
var jd=JSON.parse(xhr.responseText);
id('lbl_adc').innerHTML=jd.adc;
id('lbl_but').innerHTML=(jd.but)?'pressed':'released';
}
};
xhr.open('GET','ja',true);
xhr.send();
}
setInterval(loadValues, 500);
</script>
</body>)";
