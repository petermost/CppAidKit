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

#include "PERAAboutDialog.hpp"
#include <pera_software/company/PERA.hpp>
#include <QFile>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>

namespace pera_software { namespace company { namespace qt {

PERAAboutDialog::PERAAboutDialog( QWidget *parent )
	: QDialog( parent ) {

	QLabel *peraLogo = new QLabel;
	peraLogo->setAlignment( Qt::AlignHCenter );
	Q_ASSERT( QFile::exists( PERA::LOGO_NAME ));
	peraLogo->setPixmap( QPixmap( PERA::LOGO_NAME ));

	auto peraUrl = new QLabel;
	peraUrl->setOpenExternalLinks( true );
	peraUrl->setAlignment( Qt::AlignHCenter );
	peraUrl->setText( QString( "<a href=\"%1\">%2</a>" ).arg( PERA::FULL_DOMAIN_NAME ).arg( PERA::FULL_NAME ));

	auto buttons = new QDialogButtonBox( QDialogButtonBox::Ok );
	connect( buttons, &QDialogButtonBox::accepted, this, &QDialog::accept );

	auto layout = new QVBoxLayout( this );
	layout->addWidget( peraLogo );
	layout->addWidget( peraUrl );
	layout->addWidget( buttons );

	setLayout( layout );
}

} } }
