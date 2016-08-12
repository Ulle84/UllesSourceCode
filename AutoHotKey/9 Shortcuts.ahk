;-------------------------------------------------------------------------------
; auto correction
;-------------------------------------------------------------------------------
; Syntax:   :*:typedWrong::typedCorrectly
; trigger is not case sensitive
;-------------------------------------------------------------------------------
:*:baord::board
:*:geschreiben::geschrieben
:*:gschrieben::geschrieben
:*:Pyhton::Python
:*:postion::position
:*:widht::width
:*:nicth::nicht

;-------------------------------------------------------------------------------
; hotstrings - triggered with '#'
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


; dynamic cast
:*:dc#::
SendInput %clipboard%* p%clipboard% = dynamic_cast<%clipboard%*>(){;}{Enter}if (p%clipboard%){Enter}{{}{Enter}{Enter}{}}{up 4}{End}{left 2}
return

; #include "clipboard"
:*:in#::
SendInput {#}include "%clipboard%"
return

; #include <clipboard>
:*:inc#::
SendInput {#}include <%clipboard%>
return

; for loop iterator
:*:it#::
SendInput for (it = %clipboard%.begin(); it {!}= %clipboard%.end(); {+}{+}it){Enter}{{}{Enter}{Enter}{}}{Up}{Tab}
return

; for loop iterator 2
:*:it2#::
SendInput for (it2 = %clipboard%.begin(); it2 {!}= %clipboard%.end(); {+}{+}it2){Enter}{{}{Enter}{Enter}{}}{Up}{Tab}
return

; for loop iterator 3
:*:it3#::
SendInput for (it3 = %clipboard%.begin(); it3 {!}= %clipboard%.end(); {+}{+}it3){Enter}{{}{Enter}{Enter}{}}{Up}{Tab}
return

; for loop iterator 4
:*:it4#::
SendInput for (it4 = %clipboard%.begin(); it4 {!}= %clipboard%.end(); {+}{+}it4){Enter}{{}{Enter}{Enter}{}}{Up}{Tab}
return

; for loop iterator - auto
:*:ita#::
SendInput for (auto it = %clipboard%.begin(); it {!}= %clipboard%.end(); {+}{+}it){Enter}{{}{Enter}{Enter}{}}{Up}{Tab}
return

; for loop iterator 2 - auto
:*:ita2#::
SendInput for (auto it2 = %clipboard%.begin(); it2 {!}= %clipboard%.end(); {+}{+}it2){Enter}{{}{Enter}{Enter}{}}{Up}{Tab}
return

; for loop iterator 3 - auto
:*:ita3#::
SendInput for (auto it3 = %clipboard%.begin(); it3 {!}= %clipboard%.end(); {+}{+}it3){Enter}{{}{Enter}{Enter}{}}{Up}{Tab}
return

; for loop iterator 4 - auto
:*:ita4#::
SendInput for (auto it4 = %clipboard%.begin(); it4 {!}= %clipboard%.end(); {+}{+}it4){Enter}{{}{Enter}{Enter}{}}{Up}{Tab}
return

; member asignment
:*:ma#::
SendInput m_%clipboard% = %clipboard%{;}
return

; hashtag
:*:tag#::
SendInput //{Space}{#}_UBE{Space}
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

; daily notes
:*:dn#::
FormatTime, CurrentDateTime,, ddd dd.MM.yyyy
SendInput {Enter}{#}{#} %CurrentDateTime%{Esc}{Enter}*{Space}Administratives{Enter}{Space 2}*{Space}{Enter}{Backspace 2}*{Space}Build & Release{Enter}{Space 2}*{Space}{Enter}{Backspace 2}*{Space}MatrixKit{Enter}{Space 2}*{Space}{Enter}{Backspace 2}*{Space}VernissageKit{Enter}{Space 2}*{Space}{Enter}{Backspace 2}
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
; Signatures
;-------------------------------------------------------------------------------

; rem signuture
:*:rsig#::
FormatTime, CurrentDateTime,, yyyy-MM-dd HH:mm
SendInput rem %CurrentDateTime% UBE
return

; rem signature short
:*:rsigs#::
FormatTime, CurrentDateTime,, yyyy-MM-dd
SendInput rem %CurrentDateTime% UBE
return

; signature
:*:sig#::
FormatTime, CurrentDateTime,, yyyy-MM-dd (ddd) HH:mm
SendInput %CurrentDateTime% UBE
return

; signature short
:*:sigs#::
FormatTime, CurrentDateTime,, yyyy-MM-dd
SendInput %CurrentDateTime% UBE
return

;-------------------------------------------------------------------------------
; eMail
;-------------------------------------------------------------------------------
:*:int#::Hallo ,`n`n`n`nGruß`nUlrich`n`nTelefon: 306`nRaum: B 208{up 8}{End}{left 1}
:*:intf#::Hallo Frau ,`n`n`n`nHerzliche Grüße`nUlrich Belitz`n`nTelefon: 306`nRaum: B 208{up 8}{End}{left 1}
:*:inth#::Hallo Herr ,`n`n`n`nHerzliche Grüße`nUlrich Belitz`n`nTelefon: 306`nRaum: B 208{up 8}{End}{left 1}
:*:mail#::Ulrich.Belitz@ScientaOmicron.com
:*:sgf#::Sehr geehrte Frau ,`n`n`n`nMit freundlichen Grüßen`nUlrich Belitz{up 5}{End}{left 1}
:*:sgh#::Sehr geehrter Herr ,`n`n`n`nMit freundlichen Grüßen`nUlrich Belitz{up 5}{End}{left 1}

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
:*:adm#::Administratives
:*:ahk#::AutoHotKey
:*:av#::available
:*:br#::Build & Release
:*:bzgl#::bezüglich
:*:ci#::Continous Improvement
:*:du#::Danke{Space}und{Space}
:*:edp#::ESpDepthProfile
:*:en#::enabled
:*:eof#::end of file - only comments following
:*:fyi#::for your information
:*:ggf#::gegebenfalls
:*:ich#::ich (Ulrich Belitz)
:*:lg#::Liebe Grüße`nUlle
:*:mfg#::Mit freundlichen Grüßen
:*:mk#::MatrixKit
:*:nc#::no comment
:*:nec#::necessary
:*:shs#::siehe anhängenden Screenshot
:*:so#::ScientaOmicron
:*:unnec#::unnecessary
:*:v#::Vernissage
:*:vd#::Vielen Dank{!}
:*:vdiv#::Vielen Dank im Voraus{!}
:*:vis#::visible
:*:visu#::visualization
:*:vk#::VernissageKit
:*:vs#::Visual Studio
:*:vs13#::Visual Studio 2013
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

;end of file - only comments following

;-------------------------------------------------------------------------------
; TODO -> moved to Visual Assist Snippets
;-------------------------------------------------------------------------------
;:*:td#::// TODO{Space}
;:*:tda#::// TODO @all:{Space}
;:*:tdc#::// TODO change after testing
;:*:tdci#::// TODO correct implementation
;:*:tdd#::// TODO delete
;:*:tdi#::// TODO implement this functionality
;:*:tdn#::// TODO is this necessary?
;:*:tdr#::// TODO remove this line after testing
;:*:tds#::// TODO @all SANITIZE:{Space}
;:*:tdu#::// TODO @ube:{Space}
;:*:tdv#::// TODO verify correct behavior

;:*:dox#::
;(
;/**
;* \brief  Exemplarische Funktion
;*
;*         Diese Funktion gibt den übergebenen Parameter
;*         auf der Konsole aus.
;*
;* \param      parameter   Auszugebender Parameter
;* \return                 Status-Code
;*
;*/
;)

;:*:80#::
;(
;0        1         2         3         4         5         6         7         8
;12345678901234567890123456789012345678901234567890123456789012345678901234567890
;)

;:*:120#::
;(
;0        1         2         3         4         5         6         7         8         9        10        11        12 
;123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
;)

;:*:/*#::
;(
;/*******************************************************************************
;
;*******************************************************************************/
;)

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