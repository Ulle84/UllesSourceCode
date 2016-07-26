﻿; search help topic: hotstring

; most of the hotstrings are triggered with #

; 2012-06-05 16:43 UBE
; bei mehrfach deklarierten Befehlen entscheidet das erste Vorkommen (first come, first serve)

; --------------------------------------------------------------------------------
; Mitarbeiter (alphabetisch nach hotstring sortiert - hotstring = Kuerzel)
; --------------------------------------------------------------------------------
:*:bto#::Boni Tom
:*:dst#::Dirk Stahl
:*:lpc#::Long-Phi Chau
:*:pb#::Peter Baumann
:*:pz#::Philipp Zeigermann
:*:she#::Siegfried Heinrich
:*:rh#::Ragnar Hoffmann
:*:tr#::Thomas Roth
:*:ube#::Ulrich Belitz
:*:uf#::Uwe Fuchs

; --------------------------------------------------------------------------------
; Abkuerzungen (alphabetisch nach hotstring sortiert)
; --------------------------------------------------------------------------------
:*:+#::*{Space}
:*:<#::&lt;
:*:>#::&gt;
:*:-#::--------------------------------------------------------------------------------
:*:_#::________________________________________________________________________________
:*:as#::* formated by AStyle
:*:ahk#::AutoHotKey
:*:bp#::bool breakPoint = true;{F9}
:*:bzgl#::bezüglich
:*:cc#::* code cleaned
:*:cql#::const QList<>&{Left}{Left}
:*:cqs#::const QString&
:*:cqsl#::const QStringList&
:*:eof#::end of file - only comments following
:*:fyi#::for your information
:*:ggf#::gegebenfalls
:*:ic#::{+} initial commit
:*:ich#::ich (Ulrich Belitz)
:*:id#::id=""
:*:lg#::Liebe Grüße`nUlle
:*:mail#::Ulrich.Belitz@ScientaOmicron.com
:*:mfg#::Mit freundlichen Grüßen
:*:nc#::no comment
:*:nec#::necessary
:*:qd#::qDebug() << ""{;}{Left}{Left}
:*:ql#::QList<>{Left}
:*:qm#::QMap<>{Left}
:*:qs#::QString
:*:qsl#::QStringList
:*:so#::ScientaOmicron
:*:rf#::return false{;}
:*:rt#::return true{;}
:*:san#::// TODO @all SANITIZE:{Space}
:*:td#::// TODO{Space}
:*:tda#::// TODO @all:{Space}
:*:tdc#::// TODO change after testing
:*:tdd#::// TODO delete
:*:tdi#::// TODO implement this functionality
:*:tdn#::// TODO is this necessary?
:*:tdr#::// TODO remove this line after testing
:*:tdu#::// TODO @ube:{Space}
:*:uc#::* under construction
:*:vd#::Vielen Dank{!}
:*:vdiv#::Vielen Dank im Voraus{!}
:*:zb#::zum Beispiel
:*:zdi#::Zu Deiner Information

; --------------------------------------------------------------------------------
; Autokorrektur
; --------------------------------------------------------------------------------
; Syntax:   :*:falschgeschrieben::richtiggeschrieben
; trigger is not case sensitive
; --------------------------------------------------------------------------------
:*:baord::board
:*:geschreiben::geschrieben
:*:gschrieben::geschrieben
:*:Pyhton::Python
:*:postion::position
:*:widht::width


; --------------------------------------------------------------------------------
; Komplexe Ausdruecke (teilweise mit Berechnungen)
; --------------------------------------------------------------------------------

; daily notes
:*:dn#::
FormatTime, CurrentDateTime,, dd.MM.yyyy
SendInput {#}{#} %CurrentDateTime%{Esc}{Enter}*{Space}
return

; image from clipboard in mark-down-syntax
:*:i#::
SendInput {!}{[}{]}(%clipboard%)
return

; link from clipboard in mark-down-syntax
:*:l#::
SendInput {[}{]}(%clipboard%)
return

; member asignment
:*:ma#::
SendInput m_%clipboard% = %clipboard%{;}
return

; redmine link from clipboard in mark-down-syntax
:*:rml#::
SendInput {[}Redmine{]}(%clipboard%)
return

; for loop iterator
:*:it#::
SendInput for (auto it = %clipboard%.begin(); it {!}= %clipboard%.end(); it{+}{+}){Enter}{{}{Enter}{Enter}{}}{Up}
return

; for loop iterator 2
:*:it2#::
SendInput for (auto it2 = %clipboard%.begin(); it2 {!}= %clipboard%.end(); it2{+}{+}){Enter}{{}{Enter}{Enter}{}}{Up}
return

; for loop iterator 3
:*:it3#::
SendInput for (auto it3 = %clipboard%.begin(); it3 {!}= %clipboard%.end(); it3{+}{+}){Enter}{{}{Enter}{Enter}{}}{Up}
return

; for loop iterator 4
:*:it4#::
SendInput for (auto it4 = %clipboard%.begin(); it4 {!}= %clipboard%.end(); it4{+}{+}){Enter}{{}{Enter}{Enter}{}}{Up}
return

; code block in mark-down-syntax
:*:c#::
SendInput {ASC 96}{ASC 96}{ASC 96}{Enter}{Enter}{ASC 96}{ASC 96}{ASC 96}{Up}
return

; hashtag
:*:tag#::
SendInput //{Space}{#}_UBE{Space}
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

:*:übermorgen#::
var1 =  ; Make it blank so that the below will use the current time instead.
var1 += 2, days
FormatTime, Tomorrow, %var1%, dddd dd.MM.yyyy
SendInput übermorgen (%Tomorrow%)
return

:*:rsig#:: ; rem signuture
FormatTime, CurrentDateTime,, yyyy-MM-dd HH:mm
SendInput rem %CurrentDateTime% UBE
return

:*:rsigs#:: ; rem signature short
FormatTime, CurrentDateTime,, yyyy-MM-dd
SendInput rem %CurrentDateTime% UBE
return

:*:sig#:: ; signature
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
:*:int#::Hallo ,`n`n`n`nGruß`nUlrich`n`nTelefon: 306`nRaum: B 208{up 8}{End}{left 1}
:*:intf#::Hallo Frau ,`n`n`n`nHerzliche Grüße`nUlrich Belitz`n`nTelefon: 306`nRaum: B 208{up 8}{End}{left 1}
:*:inth#::Hallo Herr ,`n`n`n`nHerzliche Grüße`nUlrich Belitz`n`nTelefon: 306`nRaum: B 208{up 8}{End}{left 1}
:*:sgh#::Sehr geehrter Herr ,`n`n`n`nMit freundlichen Grüßen`nUlrich Belitz{up 5}{End}{left 1}
:*:sgf#::Sehr geehrte Frau ,`n`n`n`nMit freundlichen Grüßen`nUlrich Belitz{up 5}{End}{left 1}

; --------------------------------------------------------------------------------
; Templates for Programming
; --------------------------------------------------------------------------------
:*:a#::{{}
:*:s#::{}}
:*:d#::{[}{]}{left 1}
:*:f#::false
:*:g#::{Space}{|}{|}{Space}
:*:h#::{Space}{&}{&}{Space}
:*:j#::m_
:*:t#::true

:*:dox#::
(
/**
* \brief  Exemplarische Funktion
*
*         Diese Funktion gibt den übergebenen Parameter
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

:*:120#::
(
0        1         2         3         4         5         6         7         8         9        10        11        12 
123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
)

:*:/*#::
(
/*******************************************************************************

*******************************************************************************/
)

; --------------------------------------------------------------------------------
; Sonstiges
; --------------------------------------------------------------------------------
:*:bug#::
(
*pre-condition:* 
*trigger:* 
*findings:*  
)

;end of file - only comments following  

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
; Hotkeys
; --------------------------------------------------------------------------------
;^NumPad9::                                                                 ; Convert text to upper
; 
; StringUpper Clipboard, Clipboard
; SendInput %Clipboard%
;RETURN