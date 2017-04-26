; search help topic: hotstring

; most of the hotstrings are triggered with #

; 2012-06-05 16:43 UBE
; bei mehrfach deklarierten Befehlen entscheidet das erste Vorkommen (first come, first serve)

; --------------------------------------------------------------------------------
; Abkuerzungen (alphabetisch nach hotstring sortiert)
; --------------------------------------------------------------------------------
:*:<#::&lt;
:*:>#::&gt;
:*:-#::--------------------------------------------------------------------------------
:*:_#::________________________________________________________________________________
:*:acq#::ViAcqui
:*:adm#::Administrator
:*:cl#::class=""
:*:bzgl#::bez�glich
:*:fyi#::for your information
:*:ggf#::gegebenfalls
:*:ic#::[*] initial commit
:*:ich#::ich (Ulrich Belitz)
:*:id#::id=""
:*:lg#::Liebe Gr��e`nUlle
:*:mfg#::Mit freundlichen Gr��en
:*:mv#::Matrix Vision
:*:nc#::no comment
:*:pob#::[*] preparation of build
:*:td#::// TODO 
:*:tdc#::// TODO change after testing
:*:tdd#::// TODO delete
:*:tdr#::// TODO remove this line after testing
:*:tdi#::// TODO implement this functionality
:*:uc#::[*] under construction
:*:vd#::Vielen Dank{!}
:*:vdiv#::Vielen Dank im Voraus{!}
:*:zb#::zum Beispiel
:*:zdi#::Zu Deiner Information

; --------------------------------------------------------------------------------
; HTML-Codevervollstaendigung (alphabetisch nach hotstring sortiert)
; --------------------------------------------------------------------------------
;   :*b0:<a:: href=""></a>{left 6}
;   :*b0:<body::></body>{left 7}
;   :*b0:<br:: />
;   :*b0:<code::></code>{left 7}
;   :*b0:<div::>`n`n</div>{left 6}{up 1}
;   :*b0:<h1::></h1>{left 5}
;   :*b0:<h2::></h2>{left 5}
;   :*b0:<h3::></h3>{left 5}
;   :*b0:<h4::></h4>{left 5}
;   :*b0:<h5::></h5>{left 5}
;   :*b0:<h6::></h6>{left 5}
;   :*b0:<head::></head>{left 7}
;   :*b0:<hr:: />
;   :*b0:<html::></html>{left 7}
;   :*b0:<img:: src="" title="" />{left 13}
;   :*b0:<li::></li>{left 5}
;   :*b0:<ol::></ol>{left 5}
;   :*b0:<span::></span>{left 7}
;   :*b0:<table::></table>{left 8}
;   :*b0:<title::></title>{left 8}
;   :*b0:<td::></td>{left 5}
;   :*b0:<th::></th>{left 5}
;   :*b0:<tr::></tr>{left 5}
;   :*b0:<ul::>`n`n</ul>{left 5}{up 1}

; --------------------------------------------------------------------------------
; Autokorrektur
; --------------------------------------------------------------------------------
; Syntax:   :*:falschgeschrieben::richtiggeschrieben
; --------------------------------------------------------------------------------
:*:geschreiben::geschrieben
:*:gschrieben::geschrieben
:*:Pyhton::Python
:*:widht::width
:*:baord::board

; --------------------------------------------------------------------------------
; Komplexe Ausdruecke (teilweise mit Berechnungen)
; --------------------------------------------------------------------------------

; daily notes
:*:dn#::
FormatTime, CurrentDateTime,, dd.MM.yyyy
SendInput {#}{#} %CurrentDateTime%`n{*}{Space}
return

; image from clipboard in mark-down-syntax
:*:img#::
SendInput {!}{[}{]}(%clipboard%)
return

; link from clipboard in mark-down-syntax
:*:link#::
SendInput {[}{]}(%clipboard%)
return

; jira link from clipboard in mark-down-syntax
:*:jlink#::
SendInput {[}JIRA{]}(%clipboard%)
return

:*:dt#::
FormatTime, CurrentDateTime,, yyyy-MM-dd
SendInput %CurrentDateTime%
return

:*:date#::
FormatTime, CurrentDateTime,, dd.MM.yyyy
SendInput %CurrentDateTime%
return

:*:time#::
FormatTime, CurrentDateTime,, hh:mm
SendInput %CurrentDateTime%
return

:*:now#::
FormatTime, CurrentDateTime,, dd.MM.yyyy HH:mm
SendInput %CurrentDateTime%
return

:*:heute#::
FormatTime, CurrentDateTime,, dddd dd.MM.yyyy
SendInput heute (%CurrentDateTime%)
return

:*:morgen#::
var1 =  ; Make it blank so that the below will use the current time instead.
var1 += 1, days
FormatTime, Tomorrow, %var1%, dddd dd.MM.yyyy
SendInput morgen (%Tomorrow%)
return

:*:�bermorgen#::
var1 =  ; Make it blank so that the below will use the current time instead.
var1 += 2, days
FormatTime, Tomorrow, %var1%, dddd dd.MM.yyyy
SendInput �bermorgen (%Tomorrow%)
return

:*:rsig#:: ; rem signuture
FormatTime, CurrentDateTime,, yyyy-MM-dd HH:mm
SendInput rem %CurrentDateTime% UBE 
return

:*:rsigs#:: ; rem signature short
FormatTime, CurrentDateTime,, yyyy-MM-dd
SendInput rem %CurrentDateTime% UBE
return

:*:sig#:: ; signutare
FormatTime, CurrentDateTime,, yyyy-MM-dd (ddd) HH:mm
SendInput %CurrentDateTime% UBE
return

:*:sigs#:: ; signature short
FormatTime, CurrentDateTime,, yyyy-MM-dd
SendInput %CurrentDateTime% UBE
return

; --------------------------------------------------------------------------------
; eMail Signaturen
; --------------------------------------------------------------------------------
:*:int#::Hallo ,`n`n`n`nGru�`nUlrich`n`nTelefon: 386`nRaum: 14-OG3-VL-01{up 8}{End}{left 1}
:*:sgh#::Sehr geehrter Herr ,`n`n`n`nMit freundlichen Gr��en`nUlrich Belitz{up 5}{End}{left 1}
:*:sgf#::Sehr geehrte Frau ,`n`n`n`nMit freundlichen Gr��en`nUlrich Belitz{up 5}{End}{left 1}

; --------------------------------------------------------------------------------
; Templates for Programming
; --------------------------------------------------------------------------------
:*:a#::{{}
:*:s#::{}}
:*:d#::{[}{]}{left 1}
:*:f#::false
:*:g#::{Space}{|}{|}{Space}
:*:t#::true
:*:*#::[*]{Space}

:*:dox#::
(
/**
* \brief  Exemplarische Funktion
*
*         Diese Funktion gibt den �bergebenen Parameter
*         auf der Konsole aus.
*
* \param      parameter   Auszugebender Parameter
* \return                 Status-Code
*
*/
)

:*:80#::
(
0        1         2         3         4         5         6         7         8
12345678901234567890123456789012345678901234567890123456789012345678901234567890
)

:*://#::
(
//------------------------------------------------------------------------------
)

:*:/*#::
(
/*******************************************************************************

*******************************************************************************/
)



; --------------------------------------------------------------------------------
; Sonstiges
; --------------------------------------------------------------------------------
:*:jira#::
SendInput Die Aufgabe wurde erledigt.`n`nBitte das Paket %clipboard% verwenden.`n`nBitte verifizieren und Vorgang schlie�en.
return
:*:test::testc