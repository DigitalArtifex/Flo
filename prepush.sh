ICONS="$HOME/.config/DigitalArtifex/Flo/icons"
THEMES="$HOME/.config/DigitalArtifex/Flo/themes"
ICONSDEFAULT="$PWD/data/default/icons"
THEMESDEFAULT="$PWD/data/default/themes"
DEFAULTARCHIVE="$PWD/data/default/default.zip"
DEFAULT="$PWD/data/default/"

echo "Removing icons"
rm -rf $ICONSDEFAULT
echo "Copying icons"
cp -r $ICONS $ICONSDEFAULT

echo "Removing Themes"
rm -rf $THEMESDEFAULT
echo "Copying Themes"
cp -r $THEMES $THEMESDEFAULT

echo "Removing archive"
rm -f $DEFAULTARCHIVE
echo "Creating archive"
zip -r $DEFAULTARCHIVE $DEFAULT

echo "Finished"
