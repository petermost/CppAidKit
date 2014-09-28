// Copyright 2014 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the CppAidKit library.
//
// CppAidKit is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppAidKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

#include <pera_software/aidkit/qt/AboutDialog.hpp>
#include <pera_software/aidkit/qt/Images.hpp>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFile>

namespace pera_software { namespace aidkit { namespace qt {

AboutDialog::AboutDialog(QWidget *parent)
	: QDialog(parent)
{
	auto peraLogo = new QLabel;
	peraLogo->setAlignment( Qt::AlignHCenter );
	Q_ASSERT( QFile::exists( Images::PERALogo ));
	peraLogo->setPixmap( QPixmap( Images::PERALogo ));

	auto peraUrl = new QLabel;
	peraUrl->setOpenExternalLinks( true );
	peraUrl->setAlignment( Qt::AlignHCenter );
	peraUrl->setText( "<a href=\"http://www.PERA-Software.com\">PERA Software Solutions GmbH</a>" );

	auto buttons = new QDialogButtonBox( QDialogButtonBox::Ok );
	connect( buttons, &QDialogButtonBox::accepted, this, &QDialog::accept );

	auto layout = new QVBoxLayout( this );
	layout->addWidget( peraLogo );
	layout->addWidget( peraUrl );
	layout->addWidget( buttons );

	setLayout( layout );
}

} } }
