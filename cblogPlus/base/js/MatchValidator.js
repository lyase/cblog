#ifndef MATCH_VALIDATOR_JS
#define MATCH_VALIDATOR_JS

/* Note: this is at the same time valid JavaScript and C++. */

WT_DECLARE_WT_MEMBER
(2, JavaScriptConstructor, "MatchValidator",
   function(mandatory, otherId, errorMsg) {
     this.validate = function(text) {
       var otherEle = document.getElementById(otherId);
       if (otherEle.tagName.toUpperCase() == "INPUT")
         var otherText = otherEle.value;
       else if (otherEle.tagName.toUpperCase() == "TEXTAREA")
         var otherText = otherEle.getInnerHTML();
       if (text == otherText)
         return { valid: true };
       else
         return {
           valid: false,
           message: errorMsg
         };
     };
   }
);

#endif // MATCH_VALIDATOR_JS
