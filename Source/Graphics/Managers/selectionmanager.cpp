#include "selectionmanager.h"

namespace Graphics
{

SelectionManager::Modifiers SelectionManager::generateSelectionModifiers(QMouseEvent *event)
{
    auto flags = Modifiers();
    if (event->modifiers().testFlag(Qt::ControlModifier))
        flags = flags | Modifier::CtrlModifier;

    if (event->modifiers().testFlag(Qt::ShiftModifier))
        flags = flags | Modifier::ShiftModifier;

    if (event->buttons().testFlag(Qt::RightButton))
        flags = flags | Modifier::RightButtonModifier;

    return flags;
}

SelectionManager::SelectionManager()
{}

SelectionManager::SelectionType SelectionManager::getSelectionTypeForObject(SelectionManager::SelectableObject *object)
{
    if (object->getType() == SelectableObject::Track)
        return TracksSelected;
    if (object->getType() == SelectableObject::Clip)
        return ClipsSelected;
    if (object->getType() == SelectableObject::MidiNote)
        return MidiNotesSelected;

    return NoSelection;
}

void SelectionManager::setSelectionType(SelectionType type)
{
    clearSelection();
    mSelectionType = type;

    emit selectionChanged();
}

SelectionManager::SelectionType SelectionManager::getSelectionType() const
{
    return mSelectionType;
}

void SelectionManager::objectSelected(SelectableObject *object, QMouseEvent *event)
{
    objectSelected(object, generateSelectionModifiers(event));
}

void SelectionManager::objectSelected(SelectableObject *object, QFlags<Modifier> modifiers)
{
    if (getSelectionTypeForObject(object) != mSelectionType)
        setSelectionType(getSelectionTypeForObject(object));

    QPointer<SelectableObject> ptr(object);

    if (modifiers.testFlag(RightButtonModifier)) {
        if (!mSelectedObjects.contains(ptr)) {
            setSelectionType(object->getType() == SelectableObject::Clip ? ClipsSelected : TracksSelected);
            mSelectedObjects.push_back(ptr);
            ptr->setSelectedState(true);
        }
    }
    else {
        if (modifiers.testFlag(CtrlModifier)) {
            if (mSelectedObjects.contains(ptr)) {
                mSelectedObjects.remove(mSelectedObjects.indexOf(ptr));
                ptr->setSelectedState(false);
            }
            else {
                mSelectedObjects.push_back(ptr);
                ptr->setSelectedState(true);
            }
        }
        else {
            setSelectionType(getSelectionTypeForObject(object));
            mSelectedObjects.push_back(ptr);
            ptr->setSelectedState(true);
        }
    }

    emit selectionChanged();
}

QVector<QPointer<SelectionManager::SelectableObject>> SelectionManager::getSelectedObjects() const
{
    return mSelectedObjects;
}

void SelectionManager::setSelectedArea(int startTrackIndex, int startSample, int nbTracks, int nbSamples)
{
    if (mSelectionType != AreaSelected)
        return;

    mSelectedArea.startTrackIndex = startTrackIndex;
    mSelectedArea.startSample = startSample;
    mSelectedArea.nbTracks = nbTracks;
    mSelectedArea.nbSamples = nbSamples;

    emit selectionChanged();
}

void SelectionManager::setSelectedArea(SelectionArea area)
{
    if (mSelectionType != AreaSelected)
        return;

    mSelectedArea = area;

    emit selectionChanged();
}

SelectionManager::SelectionArea SelectionManager::getSelectedArea() const
{
    return mSelectedArea;
}

void SelectionManager::clearSelection()
{
    for (const auto &obj: mSelectedObjects) {
        obj->setSelectedState(false);
    }

    mSelectedObjects.clear();

    mSelectedArea = SelectionArea();
    mSelectionType = NoSelection;
}

} // namespace Graphics
