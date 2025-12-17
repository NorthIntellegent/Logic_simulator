#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Actions\Action.h"
#include "Components\Component.h"
#include "Defs.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include <stack>

using namespace std;

// Main class that manages everything in the application.
class ApplicationManager {

  enum { MaxCompCount = 200, MaxActionHistory = 50 }; // Max no of Components

private:
  int CompCount; // Actual number of Components
  Component
      *CompList[MaxCompCount]; // List of all Components (Array of pointers)

  // Clipboard info for copy/cut/paste (stores type name, not pointer)
  struct ClipboardInfo {
    string typeName;
    bool hasData;
  } m_Clipboard;

  // Action history for Undo/Redo
  Action *UndoStack[MaxActionHistory];
  Action *RedoStack[MaxActionHistory];
  int UndoCount;
  int RedoCount;

  Output *OutputInterface; // pointer to the Output Clase Interface
  Input *InputInterface;   // pointer to the Input Clase Interface

public:
public:
  ApplicationManager(); // constructor

  // Reads the required action from the user and returns the corresponding
  // action type
  ActionType GetUserAction();

  // Creates an action and executes it
  void ExecuteAction(ActionType);

  void UpdateInterface(); // Redraws all the drawing window

  // Gets a pointer to Input / Output Object
  Output *GetOutput();
  Input *GetInput();

  // Adds a new component to the list of components
  void AddComponent(Component *pComp);

  Component *GetComponentByPosition(int x, int y);

  void DeleteComponent(Component *pComp);

  void SaveCircuit(string filename);
  void LoadCircuit(string filename);

  // Accessor methods for simulation
  int GetComponentCount() const;
  Component *GetComponent(int index) const;
  Component *GetComponentByID(int id) const;

  // Clipboard methods for copy/cut/paste
  void SetClipboard(const string &typeName) {
    m_Clipboard.typeName = typeName;
    m_Clipboard.hasData = true;
  }
  string GetClipboardTypeName() const { return m_Clipboard.typeName; }
  bool HasClipboardData() const { return m_Clipboard.hasData; }

  // Multi-selection helpers
  int GetSelectedCount() const;
  void ClearAllSelections();
  void DeleteAllSelected();
  void MoveAllSelected(int dx, int dy);

  // Undo/Redo system
  void AddToUndoStack(Action *pAction);
  void PerformUndo();
  void PerformRedo();
  void ClearRedoStack();

  // destructor
  ~ApplicationManager();
};

#endif