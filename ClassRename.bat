@rem = '--*-Perl-*--
@echo off
perl -x -S %0 %*
goto endofperl
@rem ';
#!/usr/bin/perl
###############################################################################
#
# Datei                 : $RCSfile: clsrename.bat,v $
#
# Letzte Aenderung
#   Autor               : $Author: ube $
#   Datum               : $Date: 2012/07/02 17:28:46 $
#   Edition             : $Revision: 1.1 $
#
# Erstersteller         : schm
# Ersterstellung        : 24.08.2001
# Projekt               : allgemein (ViObjects)
#
###############################################################################
#
# Perlskript zur Konvertierung von Klassennamen
#
# schm, 24.8.2001
#
# Ziel ist es unter Vorgabe eines alten und eines neuen Namens
# alle Vorkommen dieses Namen in einem Dateibaum auszutauschen.
# Die Namensgebung ist dabei casesensitiv, d.h. Gross und Klein-
# schreibung werden unterschieden. Damit auch Makros, in denen 
# dieser Name vorkommt ersetzt werden können gibt es zwei weitere
# Muster nach denen gesucht wird:
#  1. der Name komplett in Grossbuchstaben und
#  2. der Name in Grossbuchstaben, wobei vor jedem Grossbuchstaben
#     im Original ein Unterstrich eingestzt wird.
# Da das Skript auch vorallem auch in Dateien eingesetzt werden soll,
# in denen CVS Kommentare und Revisionsgeschichten stehen ist es wichtig,
# dass in diesen Kommentaren keine Erzetzungen vorgenommen werden.
#
###############################################################################
#
#  Revisionsgeschichte
#
#  $Log: clsrename.bat,v $
#  Revision 1.1  2012/07/02 17:28:46  ube
#  + TemplateWidgetWithQt - inklusive UI-File
#
#  Revision 1.3  2010/09/28 15:02:59  ghe
#  Unittestbeispiel hinzugefügt
#
#  Revision 1.2  2009/10/13 10:33:23  ghe
#  [+] Default Namen auf ViMethDynTemplate geändert
#  [+] png, gif u. jpg auf die Ignoreliste gesetzt
#
#  Revision 1.1  2007/10/25 14:08:19  ghe
#  *** empty log message ***
#
#  Revision 1.3  2003/02/21 09:53:56  UB
#  - res in der Suffix-Ignore-Liste von clsrename.bat herausgenommen.
#
#  Revision 1.2  2002/06/12 13:15:43  UB
#  Die Defaultnamen fuer $dest und $src koennen als Argumente bei Programmaufruf angegeben werden.
#
#  Revision 1.1.1.1  2001/08/27 06:51:44  SCHM
#  Basis für eine ViObjectsmethode mit ViBVBaseVar
#
###############################################################################

use File::Find;
use File::Basename;

$dest = $ARGV[0];
$src = $ARGV[1];
if( $src eq "" ) {
  $src = "TemplateWidgetWithQt";
}

$FrageTextSrc = "Name der Klasse, die ersetzt werden soll: ($src)";
$FrageTextDest = "Name der neuen Klasse: ($dest)";
$SuffixIgnore = "obj|idb|map|pdb|ilk|exp|lib|sbr|dll|exe|pch|jpg|png|gif|tif|typ|bsc";

# Eingabe des Ursprungsnamens ($src)

print $FrageTextSrc;
$Answer=<STDIN>;
$Answer=~s/^(.*)\n$/$1/;
if( $Answer ne "" ) {
  $src=$Answer;
}

# Eingabe des neuen Namens ($dest)

print $FrageTextDest;
$Answer=<STDIN>;
$Answer=~s/^(.*)\n$/$1/;
if( $Answer ne "" ) {
  $dest=$Answer;
}

# Generiere die Ersetzungen für die define Ersetzungen

$src_def1=$src;
$src_def1=~tr\[a-z]\[A-Z]\;
$src_def2=$src;
$src_def2=~s\([a-z])([A-Z])\$1_$2\g;
$src_def2=~tr\[a-z]\[A-Z]\;

$dest_def1=$dest;
$dest_def1=~tr\[a-z]\[A-Z]\;
$dest_def2=$dest;
$dest_def2=~s\([a-z])([A-Z])\$1_$2\g;
$dest_def2=~tr\[a-z]\[A-Z]\;

# gib zur Kontrolle das Ergebnis der Ersetzungen aus
print qq{\n};
print qq{"$src" ==> "$dest"\n};
print qq{"$src_def1" ==> "$dest_def1"\n};
print qq{"$src_def2" ==> "$dest_def2"\n};
print qq{\n};

print qq{Sind diese Angaben in Ordnung [j|n]? };
$Antwort = <STDIN>;

if($Antwort=~/^[jJ]/) {

  # hiermit werden alle Unterverzeichnisse des angegebenen
  # Verzeichnisses durchlaufen und für jede gefundene
  # Datei das Unterprogramm ClsConvert aufgerufen

  finddepth(\&ClsConvert,'.');
}

###############################################################################
# 
# Funktion: ClsConvert
#
# Parameter: $_ enthält den aktuellen Dateinamen, wir befinden uns beim
#            Aufruf schon im richtigen Verzeichnis
#
###############################################################################
sub ClsConvert {

  # Teste, ob es sich um ein Verzeichnis handelt,
  # eine Binärdatei
  # oder um uns selbst
  # in allen diesen Fällen soll nichts gemacht werden

  if (! -d and !/.*\.($SuffixIgnore)$/ and !/clsrename.bat/) {

    my $InFile = $_;      # Name der Eingabedatei
    my $OutFile = $_;     # Name der Ausgabedatei (kann sich ändern)
    my $FileUnlink = 0;   # Wenn die Datei umbenannt wird zeigt diese
                          # Variable an, das das Orignal gelöscht werden kann

    # Die Namensumsetzung bei den Dateinamen ist caseinsensitiv

    if ($OutFile =~ s/(.*)($src)(.*)/$1$dest$3/i) { 
	    $FileUnlink = 1;    # Damit wird angezeigt, dass das Original 
                          # gelöscht werden soll
    }

    print "INFILE = $InFile OUTFILE = $OutFile\n";

    ###########################################################################
    #
    # Die Datei einlesen und mit den entsprechenden Ersetzungen in einen
    # Zwischenspeicher schreiben
    #

    open(INFILE,$InFile);

    my $TmpText = "";   # Zwischenspeicher für den gelesenen Text. Er muss für 
                        # jeden Durchlauf neu initialisiert werden.

    while (<INFILE>) 
    {
      # Ersetzen der Bezeichnungen

      s/$src/$dest/g;

      # Ersetzen der defines und andere Makros

      s/$src_def1/$dest_def1/g;
      s/$src_def2/$dest_def2/g;

      # Anhängen an den Zwischenspeicher

      $TmpText = join("",$TmpText,$_);
    }
    close(INFILE);

    if($FileUnlink == 1) {
      unlink($InFile);
    }
    open(OUTFILE,">$OutFile");
    print OUTFILE $TmpText;
    close(OUTFILE);
  }
}
###############################################################################
__END__
:endofperl
