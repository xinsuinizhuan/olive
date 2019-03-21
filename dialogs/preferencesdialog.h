/***

    Olive - Non-Linear Video Editor
    Copyright (C) 2019  Olive Team

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QKeySequenceEdit>
#include <QMenuBar>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QSpinBox>

#include "timeline/sequence.h"

class KeySequenceEditor;

/**
 * @brief The PreferencesDialog class
 *
 * A dialog for the global application settings. Mostly an interface for Config.
 */
class PreferencesDialog : public QDialog
{
  Q_OBJECT

public:
  /**
   * @brief PreferencesDialog Constructor
   *
   * @param parent
   *
   * QWidget parent. Usually MainWindow.
   */
  explicit PreferencesDialog(QWidget *parent = nullptr);

private slots:
  /**
   * @brief Override of accept to save preferences to Config.
   */
  virtual void accept() override;
  void reset_default_shortcut();
  void reset_all_shortcuts();
  bool refine_shortcut_list(const QString &, QTreeWidgetItem* parent = nullptr);
  void load_shortcut_file();
  void save_shortcut_file();
  void browse_css_file();
  void delete_all_previews();

private:
  void setup_ui();
  void setup_kbd_shortcuts(QMenuBar* menu);
  void setup_kbd_shortcut_worker(QMenu* menu, QTreeWidgetItem* parent);

  // used to delete previews
  // type can be: 't' for thumbnails, 'w' for waveforms, or 1 for all
  /**
   * @brief Delete disk cached preview files (thumbnails, waveforms, etc.)
   *
   * @param type
   *
   * The types of previews to
   */
  void delete_previews(char type);

  QLineEdit* custom_css_fn;
  QLineEdit* imgSeqFormatEdit;
  QComboBox* recordingComboBox;
  QRadioButton* accurateSeekButton;
  QRadioButton* fastSeekButton;
  QTreeWidget* keyboard_tree;
  QDoubleSpinBox* upcoming_queue_spinbox;
  QComboBox* upcoming_queue_type;
  QDoubleSpinBox* previous_queue_spinbox;
  QComboBox* previous_queue_type;
  QSpinBox* effect_textbox_lines_field;
  QCheckBox* use_software_fallbacks_checkbox;
  QComboBox* audio_output_devices;
  QComboBox* audio_input_devices;
  QComboBox* audio_sample_rate;
  QComboBox* language_combobox;
  QSpinBox* thumbnail_res_spinbox;
  QSpinBox* waveform_res_spinbox;
  QCheckBox* add_default_effects_to_clips;
  QComboBox* ui_style;
  Sequence sequence_settings;
#ifdef Q_OS_WIN
  QCheckBox* native_menus;
#endif

  QVector<QAction*> key_shortcut_actions;
  QVector<QTreeWidgetItem*> key_shortcut_items;
  QVector<KeySequenceEditor*> key_shortcut_fields;
};

class KeySequenceEditor : public QKeySequenceEdit {
  Q_OBJECT
public:
  KeySequenceEditor(QWidget *parent, QAction* a);
  void set_action_shortcut();
  void reset_to_default();
  QString action_name();
  QString export_shortcut();
private:
  QAction* action;
};

#endif // PREFERENCESDIALOG_H
