//wizard -> entrance


function uiOnload(){
	chgHTML();
}

function chgHTML(){
	var main_menu = document.getElementsByClassName('main_menu');
	var td_menu   = document.getElementsByClassName('td_menu');
	//ιθδΈ»θε?
	if(main_menu[0]){
		main_menu[0].style.display = 'none';
	}
	//ιθδΊηΊ§θε
	if(td_menu[0]){
		td_menu[0].style.display = 'none';
	}
}

function uiNextPage(){
	
	$H({
	    'var:menu'	: 'setup',
		'var:subpage' : 'wizsntp',
		'var:page' : 'wizard',
		'getpage'  : 'html/index.html'
	},true);
	
	//δΏε­ειηζ°ζ?
	var __data = '{stp:{},isp:{},sec:{},psd:{}}';
	if(!Cookie.Get('cache_wiz')){
		Cookie.Set('cache_wiz',__data);
	}
	
	$('uiPostForm').submit();
}

function uiCancle(){
	if(!confirm(SEcode[1012])){
		return false;
	}
	
	$H({
		'var:menu' : 'setup',
		'var:page' : 'wizard',
		'getpage'  : 'html/index.html'
	});
	
	$('uiPostForm').submit();
}

function dealWithError(){
	
}

addListeners(uiOnload, dealWithError);