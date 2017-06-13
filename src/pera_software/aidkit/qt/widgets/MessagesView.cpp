// Copyright 2017 Peter Most, PERA Software Solutions GmbH
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

#include "MessagesView.hpp"

namespace pera_software { namespace aidkit { namespace qt {

using namespace std;

MessagesView::MessagesView( QWidget *parent )
	: QListView( parent ) {
}

void MessagesView::setModel( QAbstractItemModel *model ) {
	QListView::setModel( model );

	connect( model, &QAbstractItemModel::rowsInserted, [ this ]( const QModelIndex &parent, int /* first */, int last ) {
		scrollTo( this->model()->index( last, 0, parent ));
	});
}

} } }
