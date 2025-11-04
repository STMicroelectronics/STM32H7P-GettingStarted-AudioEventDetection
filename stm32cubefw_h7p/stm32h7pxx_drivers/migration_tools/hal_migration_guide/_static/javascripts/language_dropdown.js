function switchLanguage(code)
{event.preventDefault();var currentURL=window.location.href;console.log("Current URL:",currentURL);var targetURL="";if(currentURL.includes('/i18n/'))
{if(code==='en')
{console.log("from alternate to en")
var match=currentURL.match(/(.*\/)i18n\/[a-zA-Z_-]+\/(.*\.html.*)/);targetURL=match[1]+match[2];}
else
{console.log("from alternate to alternate")
targetURL=currentURL.replace(/(.*\/)i18n\/[a-zA-Z_-]+\/(.*\.html)/,'$1'+'i18n/'+code+'/$2');}}
else
{if(code==='en')
{console.log("from en to en")
targetURL=currentURL;}
else
{console.log("from en to alternate")
targetURL=currentURL.replace(/(.*\/)(docs\/.*\.html)/,'$1'+'i18n/'+code+'/$2');if(targetURL==currentURL)
{console.log("from en to alternate: home page")
targetURL=currentURL.replace(/(.*\/)(.*\.html)/,'$1'+'i18n/'+code+'/$2');}}}
console.log("Target URL:",targetURL);window.location.href=targetURL;}