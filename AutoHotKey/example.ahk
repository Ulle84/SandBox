;-------------------------------------------------------------------------------
; auto correction
;-------------------------------------------------------------------------------
; Syntax:   :*:typedWrong::typedCorrectly
; trigger is not case sensitive
;-------------------------------------------------------------------------------
:*:baord::board
:*:Pyhton::Python
:*:postion::position
:*:widht::width

;-------------------------------------------------------------------------------
; hotstrings - triggered with '#'
; example:    
;   code:      :*:a#::{&}{&}{Space}
;   behaviour: type 'a' and then '#' -> 'a#' will be replaced by '&& '
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Programming
;-------------------------------------------------------------------------------
:*:a#::{&}{&}{Space}
:*:bp#::bool breakPoint = true;{F9}
:*:c#::''{Left}
:*:cql#::const QList<>&{Left}{Left}
:*:cqs#::const QString&
:*:cqsl#::const QStringList&
:*:en#::!={Space}
:*:eq#::=={Space}
:*:f#::false
:*:ls#::L""{Left}
:*:o#::{|}{|}{Space}
:*:qd#::qDebug() << {;}{Left 1}
:*:qds#::qDebug() << ""{;}{Left 2}
:*:ql#::QList<>{Left}
:*:qm#::QMap<>{Left}
:*:qs#::QString
:*:qsl#::QStringList
:*:r#::return {;}{Left}
:*:rc#::return ''{;}{Left 2}
:*:rf#::return false{;}
:*:ro#::return 0{;}
:*:roo#::return 0.0{;}
:*:rs#::return ""{;}{Left 2}
:*:rt#::return true{;}
:*:s#::""{Left}
:*:t#::true

; #include "clipboard"
:*:in#::
SendInput {#}include "%clipboard%"
return

; #include <clipboard>
:*:inc#::
SendInput {#}include <%clipboard%>
return

; member asignment
:*:ma#::
SendInput m_%clipboard% = %clipboard%{;}
return

;-------------------------------------------------------------------------------
; Commit Comments
;-------------------------------------------------------------------------------
:*:as#::* formated by AStyle
:*:cc#::* code cleaned
:*:ic#::{+} initial commit
:*:po#::* performance optimization
:*:uc#::* under construction

;-------------------------------------------------------------------------------
; Markdown
;-------------------------------------------------------------------------------

; code block
:*:co#::
SendInput {ASC 96}{ASC 96}{ASC 96}{Enter}{Enter}{ASC 96}{ASC 96}{ASC 96}{Up}
return

; image
:*:img#::
SendInput {!}{[}{]}(%clipboard%)
return

; link
:*:l#::
SendInput {[}{]}(%clipboard%)
return

; redmine link
:*:rl#::
SendInput {[}Redmine{]}(%clipboard%)
return

;-------------------------------------------------------------------------------
; Textile
;-------------------------------------------------------------------------------
:*:cpp#::<pre><code class="cpp">{Enter 2}</code></pre>{Up}
:*:tab#::|_. A |_. B |_. C |{Enter}| A | B | C |{Enter}|/2. row span | B | C |{Enter}|\2. col span |
:*:tl#::""{:}http{: 2}//link{shift down}{left 12}{shift up}
:*:tn#::{{}{{}thumbnail(){}}{}}{left 3}
:*:wp#::[[id|description]]{left 2}{shift down}{left 11}{shift up}
:*:xml#::<pre><code class="xml">{Enter 2}</code></pre>{Up}

;-------------------------------------------------------------------------------
; Date & Time
;-------------------------------------------------------------------------------

; today
:*:tod#::
FormatTime, CurrentDateTime,, yyyy-MM-dd
SendInput %CurrentDateTime%
return

; tomorrow
:*:tom#::
var1 =  ; Make it blank so that the below will use the current time instead.
var1 += 1, days
FormatTime, Tomorrow, %var1%, yyyy-MM-dd
SendInput %Tomorrow%
return

; yesterday
:*:yes#::
var1 =  ; Make it blank so that the below will use the current time instead.
var1 += -1, days
FormatTime, Yesterday, %var1%, yyyy-MM-dd
SendInput %Yesterday%
return

; current date and time
:*:dt#::
FormatTime, CurrentDateTime,, yyyy-MM-dd hh:mm
SendInput %CurrentDateTime%
return

; current time
:*:ti#::
FormatTime, CurrentDateTime,, hh:mm
SendInput %CurrentDateTime%
return

;-------------------------------------------------------------------------------
; Misc
;-------------------------------------------------------------------------------
:*:-#::--------------------------------------------------------------------------------
:*:_#::________________________________________________________________________________
:*:av#::available
:*:br#::Build & Release
:*:bzgl#::bezüglich
:*:du#::Danke{Space}und{Space}
:*:en#::enabled
:*:fyi#::for your information
:*:ggf#::gegebenfalls
:*:mfg#::Mit freundlichen Grüßen
:*:mk#::MatrixKit
:*:nc#::no comment
:*:nec#::necessary
:*:so#::ScientaOmicron
:*:unnec#::unnecessary
:*:v#::Vernissage
:*:vd#::Vielen Dank{!}
:*:vdiv#::Vielen Dank im Voraus{!}
:*:vk#::VernissageKit
:*:zb#::zum Beispiel
:*:zdi#::Zu Deiner Information

; bug report for redmine
:*:bug#::
(
*software version:*
*pre-condition:*
*expected behaviour:*
*trigger:*
*findings:*
*log-file/trace:*
*screenshot:*
)