//
// Created by momo783 on 13/05/2018.
//

#ifndef XES_TOLUA_FIX_H
#define XES_TOLUA_FIX_H

#include "tolua++.h"
#include "XMemBase.h"
#include "XArray.h"
#include "XMath3D.h"
#include <typeinfo>


#define TOLUA_REFID_PTR_MAPPING "toluafix_refid_ptr_mapping"
#define TOLUA_REFID_TYPE_MAPPING "toluafix_refid_type_mapping"
#define TOLUA_REFID_FUNCTION_MAPPING "toluafix_refid_function_mapping"

#define XESLuaBindCallback(...)

TOLUA_API void toluafix_open(lua_State *L);

TOLUA_API void toluafix_clear();

TOLUA_API int toluafix_pushusertype(lua_State *L,
        void *ptr,
        const char *type);


/**
 * Find the value of Ref object pointer in the Lua registry by the refid.
 * Then, remove the corresponding reference in some table in the Lua registry by refid, such as toluafix_refid_type_mapping, toluafix_refid_ptr_mapping,tolua_value_root,and so on.
 * Set the value of userdata nullptr and remove the reference of userdata in the tolua_ubox table.
 * This function is called in the destructor of the Ref automatically.
 *
 * @param L the current lua_State.
 * @param refid the value of the _luaID of a Ref object.
 * @return -1,if refid equals to 0 , type name found by refid equals to nil or corresponding userdata pointer equal to nullptr; return -2, if the Ref object pointer found by refid is nullptr; return 3, if the value corresponding to the Ref object pointer in the tolua_ubox is nil; otherwise return 0.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_remove_xobject_by_refid(lua_State *L, void *obj);

/**
 * Get the reference id of the Lua function at the given acceptable index lo of stack.
 * Meanwhile add reference about the Lua function through the toluafix_refid_function_mapping table in the Lua registry.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index lo of stack.
 * @param def useless.
 * @return 0 if the type of value at the given acceptable index lo of stack is not LUA_TFUNCTION; otherwise return the reference id.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_ref_function(lua_State *L, int lo, int def);

/**
 * Push the Lua function found by the refid in the toluafix_refid_function_mapping table in the Lua registry on the top index of the current stack.
 *
 * @param L the current lua_State.
 * @param refid reference id corresponding to the Lua function.
 * @lua NA
 * @js NA
 */
TOLUA_API void toluafix_get_function_by_refid(lua_State *L, int refid);

/**
 * Remove the reference of the Lua function corresponding to the refid in the toluafix_refid_function_mapping table in the Lua registry.
 *
 * @param L the current lua_State.
 * @param refid reference id corresponding to the Lua function.
 * @lua NA
 * @js NA
 */
TOLUA_API void toluafix_remove_function_by_refid(lua_State *L, int refid);

/**
 * Verify the value at the given acceptable index is a function or not.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index lo of stack.
 * @param type useless.
 * @param def useless.
 * @param err if trigger the error, record the error message to err.
 * @return 1 if the value at the given acceptable index is a function, otherwise return 0.
 * @lua NA
 * @js NA
 */
TOLUA_API int
toluafix_isfunction(lua_State *L, int lo, const char *type, int def, tolua_Error *err);

/// @cond
TOLUA_API int toluafix_totable(lua_State *L, int lo, int def);
/// @endcond

/**
 * Verify the value at the given acceptable index is a table or not.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index lo of stack.
 * @param type useless.
 * @param def whether has the default value.
 * @param err if trigger the error, record the error message to err.
 * @return 1 if the value at the given acceptable index is a table or have def value is not 0, otherwise return 0.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_istable(lua_State *L, int lo, const char *type, int def, tolua_Error *err);

/**
 * Print all information of the stack from the top index.
 * If the type corresponding to the index of the stack is LUA_TSTRING, LUA_TBOOLEAN or LUA_TNUMBER, it would output the value of the index,otherwise output the type name of the index.
 *
 * @param L the current lua_State.
 * @param label the string pointer to define the label of the dump information.
 * @lua NA
 * @js NA
 */
TOLUA_API void toluafix_stack_dump(lua_State *L, const char *label);


bool typeisNumber(const std::type_info &type_info);

XArray<XString> toXStringXArray(lua_State *L, int lo, int def);

template<typename T>
void pushXArray(lua_State *L, const XArray<T> *array, const char *typeName) {
    lua_newtable(L);                                                //LUA array

    if (nullptr == L)
        return;

    for (xint32 i = 0; i < array->Num(); i++) {
        T obj = (*array)[i];
        lua_pushnumber(L, (lua_Number) i + 1);                 //array index
        void *tolua_obj = Mtolua_new((T) (obj));
        tolua_pushusertype(L, tolua_obj, typeName);         //array element
        tolua_register_gc(L, lua_gettop(L));
        lua_rawset(L, -3);                                          //array[index] = element
    }
}

template<typename T>
void pushXArray(lua_State *L, const XArray<T> &array, const char *typeName) {
    lua_newtable(L);                                                //LUA array

    if (nullptr == L)
        return;

    for (xint32 i = 0; i < array.Num(); i++) {
        T obj = (array)[i];
        lua_pushnumber(L, (lua_Number) i + 1);                 //array index
        void *tolua_obj = Mtolua_new((T) (obj));
        tolua_pushusertype(L, tolua_obj, typeName);             //array element
        tolua_register_gc(L, lua_gettop(L));
        lua_rawset(L, -3);                                          //array[index] = element
    }

}

template<typename T>
void pushXArray(lua_State *L, const XArray<T *> *array, const char *typeName) {

    lua_newtable(L);

    if (nullptr == L)
        return;

    for (xint32 i = 0; i < array->Num(); i++) {
        T *obj = (*array)[i];
        lua_pushnumber(L, (lua_Number) i + 1);                 //array index
        tolua_pushusertype(L, (void *) obj, typeName);
        lua_rawset(L, -3);
    }
}

template<typename T>
void pushXArray(lua_State *L, const XArray<T *> &array, const char *typeName) {

    lua_newtable(L);

    if (nullptr == L)
        return;

    for (xint32 i = 0; i < array.Num(); i++) {
        T *obj = (array)[i];
        lua_pushnumber(L, (lua_Number) i + 1);                 //array index
        tolua_pushusertype(L, (void *) obj, typeName);
        lua_rawset(L, -3);
    }
}

template<typename T>
void pushNumXArray(lua_State *L, const XArray<T> &array) {

    lua_newtable(L);

    if (nullptr == L)
        return;

    for (xint32 i = 0; i < array.Num(); i++) {
        lua_pushnumber(L, (lua_Number) i + 1);
        tolua_pushnumber(L, array[i]);
        lua_rawset(L, -3);
    }
}

template<typename T>
void pushStringXArray(lua_State *L, const XArray<T> &array) {

    lua_newtable(L);

    if (nullptr == L)
        return;

    for (xint32 i = 0; i < array.Num(); i++) {
        lua_pushnumber(L, (lua_Number) i + 1);
        tolua_pushstring(L, array[i]);
        lua_rawset(L, -3);
    }
}

template<typename T>
void pushBoolXArray(lua_State *L, const XArray<T> &array) {

    lua_newtable(L);

    if (nullptr == L)
        return;

    for (xint32 i = 0; i < array.Num(); i++) {
        lua_pushnumber(L, (lua_Number) i + 1);
        tolua_pushboolean(L, array[i]);
        lua_rawset(L, -3);
    }
}


template<typename T>
XArray<T> toBoolXArray(lua_State *L, int lo, int def) {
    XArray<T> array;
    if (nullptr == L || lua_gettop(L) < lo)
        return array;

    tolua_Error tolua_err;
    bool ok = true;

    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if XES_DEBUG_LOG >= 1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    if (ok) {
        size_t len = lua_objlen(L, lo);
        for (xint32 i = 0; i < len; i++) {
            lua_pushboolean(L, i + 1);
            lua_gettable(L, lo);
            if (lua_isboolean(L, -1)) {
                array.Add(tolua_tonumber(L, -1, 0));
            }
            lua_pop(L, 1);
        }
    }
    return array;
}

template<typename T>
XArray<T> toNumberXArray(lua_State *L, int lo, int def) {
    XArray<T> array;
    if (nullptr == L || lua_gettop(L) < lo)
        return array;

    tolua_Error tolua_err;
    bool ok = true;

    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if XES_DEBUG_LOG >= 1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    if (ok) {
        size_t len = lua_objlen(L, lo);
        for (xint32 i = 0; i < len; i++) {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            if (lua_isnumber(L, -1)) {
                array.Add(tolua_tonumber(L, -1, 0));
            }
            lua_pop(L, 1);
        }
    }
    return array;
}


template<typename T>
XArray<T *> toPXArray(lua_State *L, int lo, int def) {
    XArray<T *> array;
    if (nullptr == L || lua_gettop(L) < lo)
        return array;

    tolua_Error tolua_err;
    bool ok = true;

    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if XES_DEBUG_LOG >= 1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    if (ok) {
        size_t len = lua_objlen(L, lo);
        for (xint32 i = 0; i < len; i++) {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            void *obj = tolua_tousertype(L, -1, 0);
            array.Add((T *) obj);
            lua_pop(L, 1);
        }
    }
    return array;
}

template<typename T>
XArray<T> toXArray(lua_State *L, int lo, int def) {
    XArray<T> array;
    if (nullptr == L || lua_gettop(L) < lo)
        return array;

    tolua_Error tolua_err;
    bool ok = true;

    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if XES_DEBUG_LOG >= 1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    if (ok) {
        size_t len = lua_objlen(L, lo);
        for (xint32 i = 0; i < len; i++) {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);

            T *t = (T *) tolua_tousertype(L, -1, 0);
            array.Add(*t);

            lua_pop(L, 1);
        }
    }
    return array;
}

//XString fix
#define tolua_pushxstring(x, y)                  tolua_pushstring(x,y.CStr())
#define tolua_isxstring                          tolua_isstring
#define tolua_toxstring                          tolua_tostring

//XArray fix
#define tolua_isxarray                           tolua_istable

//基本类型push&to fix
#define tolua_pushxarray_bool(L, arr)            pushBoolXArray(L,arr)
#define tolua_toxarray_bool                      toBoolXArray<bool>
#define tolua_pushxarray_xbool(L, arr)           pushBoolXArray(L,arr)
#define tolua_toxarray_xbool                     toBoolXArray<xbool>
#define tolua_pushxarray_xint32(L, arr)          pushNumXArray(L,arr)
#define tolua_toxarray_xint32                    toNumberXArray<xint32>
#define tolua_pushxarray_xfloat32(L, arr)        pushNumXArray(L,arr)
#define tolua_toxarray_xfloat32                  toNumberXArray<xfloat32>
#define tolua_pushxarray_XString(L, arr)         pushStringXArray(L,arr)
#define tolua_toxarray_XString                   toXStringXArray

//对象push&to fix
#define tolua_pushxarray_XETreeNode__(L, arr)                           pushXArray(L,arr,"XETreeNode")
#define tolua_pushxarray_AR__HitTestResult(L, arr)                      pushXArray(L,arr,"AR::HitTestResult")
#define tolua_pushxarray_XVECTOR2(L, arr)                               pushXArray(L,arr,"XVECTOR2")
#define tolua_pushxarray_XVECTOR3(L, arr)                               pushXArray(L,arr,"XVECTOR3")
#define tolua_pushxarray_XVECTOR4(L, arr)                               pushXArray(L,arr,"XVECTOR4")
#define tolua_pushxarray_XMATRIX4(L, arr)                               pushXArray(L,arr,"XMATRIX4")
#define tolua_pushxarray_XSkinData__IndexPairAndNormal(L, arr)          pushXArray(L,arr,"XSkinData::IndexPairAndNormal")
#define tolua_pushxarray_XSkinData__BoneNameAndOBB(L, arr)              pushXArray(L,arr,"XSkinData::BoneNameAndOBB")
#define tolua_pushxarray_XCusOBB(L, arr)                                pushXArray(L,arr,"XCusOBB")
#define tolua_pushxarray_XCusCone(L, arr)                               pushXArray(L,arr,"XCusCone")
#define tolua_pushxarray_XBone__XBoneRenderData(L, arr)                 pushXArray(L,arr,"XBone::XBoneRenderData")
#define tolua_pushxarray_XSkeleton__XSkeletonMuscleData__Muscle(L, arr) pushXArray(L,arr,"XSkeleton::XSkeletonMuscleData::Muscle")
#define tolua_pushxarray_XBlendShapeTarget__BlendShapeVertex(L, arr)    pushXArray(L,arr,"XBlendShapeTarget::BlendShapeVertex")
#define tolua_pushxarray_XBlendShapeTarget__XBlendShapeChannel(L, arr)  pushXArray(L,arr,"XBlendShapeTarget::XBlendShapeChannel")
#define tolua_pushxarray_xFaceRigBoneControl(L, arr)                    pushXArray(L,arr,"xFaceRigBoneControl")
#define tolua_pushxarray_XPFCtrlBone(L, arr)                            pushXArray(L,arr,"XPFCtrlBone")
#define tolua_pushxarray_XPinchParam(L, arr)                            pushXArray(L,arr,"XPinchParam")
#define tolua_pushxarray_XSkinData__XRenderMesh__(L, arr)               pushXArray(L,arr,"XSkinData::XRenderMesh")
#define tolua_pushxarray_XSkinData__XRawMesh__(L, arr)                  pushXArray(L,arr,"XSkinData::XRawMesh")
#define tolua_pushxarray_IXPrimitiveBase__(L, arr)                      pushXArray(L,arr,"IXPrimitiveBase")
#define tolua_pushxarray_XESkeletonInstance__(L, arr)                   pushXArray(L,arr,"XESkeletonInstance")
#define tolua_pushxarray_XUIWidget__(L, arr)                            pushXArray(L,arr,"XUIWidget")
#define tolua_pushxarray_XEActor__(L, arr)                              pushXArray(L,arr,"XEActor")
#define tolua_pushxarray_XUINode__(L, arr)                              pushXArray(L,arr,"XUINode")
#define tolua_pushxarray_XEBindSocketInstance__(L, arr)                 pushXArray(L,arr,"XEBindSocketInstance")
#define tolua_pushxarray_xes__CVObject__(L, arr)                        pushXArray(L,arr,"xes::CVObject")
#define tolua_pushxarray_xes__CVBody__Joint(L, arr)                     pushXArray(L,arr,"xes::CVBody::Joint")
#define tolua_pushxarray_xes__CVBody__(L, arr)                          pushXArray(L,arr,"xes::CVBody")
#define tolua_pushxarray_XEActorComponent__(L, arr)                     pushXArray(L,arr,"XEActorComponent")
#define tolua_pushxarray_ModuleFlag(L, arr)                             pushXArray(L,arr,"ModuleFlag")
#define tolua_pushxarray_XEMovementAttacher__MoveableComponent(L, arr)  pushXArray(L,arr,"XEMovementAttacher::MoveableComponent")
#define tolua_pushxarray_XESeqBindingCameraCuts__MetaData(L, arr)       pushXArray(L,arr,"XESeqBindingCameraCuts::MetaData")
#define tolua_pushxarray_XSkeletonMap__TrackBonePair(L, arr)            pushXArray(L,arr,"XSkeletonMap::TrackBonePair")
#define tolua_pushxarray_XEMovementAttacher__Listener__(L, arr)         pushXArray(L,arr,"XEMovementAttacher::Listener")
#define tolua_pushxarray_FxProperty__(L, arr)                           pushXArray(L,arr,"FxProperty*")
#define tolua_pushxarray_XEAnimComponentPlayList__AnimWrapper(L, arr)   pushXArray(L,arr,"XEAnimComponentPlayList::AnimWrapper")
#define tolua_pushxarray_xes__Face__(L, arr)                            pushXArray(L,arr,"xes::Face")
#define tolua_pushxarray_AR__XEARAnchor__(L, arr)                       pushXArray(L,arr,"AR::XEARAnchor")
#define tolua_pushxarray_IXEUserNodeFactory__(L, arr)                   pushXArray(L,arr,"IXEUserNodeFactory")
#define tolua_pushxarray_IXBrushPrimitive__XBrushShape(L, arr)          pushXArray(L,arr,"IXBrushPrimitive::XBrushShape")
#define tolua_pushxarray_XEHitResult(L, arr)                            pushXArray(L,arr,"XEHitResult")
#define tolua_pushxarray_Scene__(L, arr)                                pushXArray(L,arr,"Scene")
#define tolua_pushxarray_XBlendShapeChannel__TargetPair(L, arr)         pushXArray(L,arr,"XBlendShapeChannel::TargetPair")
#define tolua_pushxarray_XBlendShapeTarget(L, arr)                      pushXArray(L,arr,"XBlendShapeTarget")
#define tolua_pushxarray_IXCloth__(L, arr)                              pushXArray(L,arr,"IXCloth")
#define tolua_pushxarray_XBlendShapeChannel(L, arr)                     pushXArray(L,arr,"XBlendShapeChannel")
#define tolua_pushxarray_XSphylShapeElem(L, arr)                        pushXArray(L,arr,"XBlendShapeChannel")
#define tolua_pushxarray_xes__Hand__Joint(L, arr)                       pushXArray(L,arr,"xes::Hand::Joint")
#define tolua_pushxarray_xes__Hand__Gesture(L, arr)                     pushXArray(L,arr,"xes::Hand::Gesture")
#define tolua_pushxarray_xes__Hand__(L, arr)                            pushXArray(L,arr,"xes::Hand")
#define tolua_pushxarray_XEWorld__(L, arr)                              pushXArray(L,arr,"XEWorld")
#define tolua_pushxarray_IXEEventFactory__(L, arr)                      pushXArray(L,arr,"IXEEventFactory")
#define tolua_pushxarray_XEAnimMonElement__MetaData(L, arr)             pushXArray(L,arr,"XEAnimMonElement::MetaData")
#define tolua_pushxarray_IXSkeletalPhysicsRes__XPhyConstraintBoneNames(L, arr)\
pushXArray(L,arr,"IXSkeletalPhysicsRes::XPhyConstraintBoneNames")


#define tolua_toxarray_XETreeNode__                                     toPXArray<XETreeNode>
#define tolua_toxarray_AR__HitTestResult                                toXArray<AR::HitTestResult>
#define tolua_toxarray_XVECTOR2                                         toXArray<XVECTOR2>
#define tolua_toxarray_XVECTOR3                                         toXArray<XVECTOR3>
#define tolua_toxarray_XVECTOR4                                         toXArray<XVECTOR4>
#define tolua_toxarray_XMATRIX4                                         toXArray<XMATRIX4>
#define tolua_toxarray_XSkinData__IndexPairAndNormal                    toXArray<XSkinData::IndexPairAndNormal>
#define tolua_toxarray_XSkinData__BoneNameAndOBB                        toXArray<XSkinData::BoneNameAndOBB>
#define tolua_toxarray_XCusOBB                                          toXArray<XCusOBB>
#define tolua_toxarray_XCusCone                                         toXArray<XCusCone>
#define tolua_toxarray_XBone__XBoneRenderData                           toXArray<XBone::XBoneRenderData>
#define tolua_toxarray_XSkeleton__XSkeletonMuscleData__Muscle           toXArray<XSkeleton::XSkeletonMuscleData::Muscle>
#define tolua_toxarray_XBlendShapeTarget__BlendShapeVertex              toXArray<XBlendShapeTarget::BlendShapeVertex>
#define tolua_toxarray_XBlendShapeTarget__XBlendShapeChannel            toXArray<XBlendShapeTarget::XBlendShapeChannel>
#define tolua_toxarray_xFaceRigBoneControl                              toXArray<xFaceRigBoneControl>
#define tolua_toxarray_XPFCtrlBone                                      toXArray<XPFCtrlBone>
#define tolua_toxarray_XPinchParam                                      toXArray<XPinchParam>
#define tolua_toxarray_XSkinData__XRenderMesh__                         toPXArray<XSkinData::XRenderMesh>
#define tolua_toxarray_XSkinData__XRawMesh__                            toPXArray<XSkinData::XRawMesh>
#define tolua_toxarray_IXPrimitiveBase__                                toPXArray<IXPrimitiveBase>
#define tolua_toxarray_XUIWidget                                        toXArray<XUIWidget>
#define tolua_toxarray_xes__CVObject__                                  toPXArray<xes::CVObject>
#define tolua_toxarray_xes__CVBody__Joint                               toXArray<xes::CVBody::Joint>
#define tolua_toxarray_xes__CVBody__                                    toPXArray<xes::CVBody>
#define tolua_toxarray_XEActorComponent__                               toPXArray<XEActorComponent>
#define tolua_toxarray_ModuleFlag                                       toXArray<ModuleFlag>
#define tolua_toxarray_XEMovementAttacher__MoveableComponent            toXArray<XEMovementAttacher::MoveableComponent>
#define tolua_toxarray_XESeqBindingCameraCuts__MetaData                 toXArray<XESeqBindingCameraCuts::MetaData>
#define tolua_toxarray_XSkeletonMap__TrackBonePair                      toXArray<XSkeletonMap::TrackBonePair>
#define tolua_toxarray_XEMovementAttacher__Listener__                   toPXArray<XEMovementAttacher::Listener>
#define tolua_toxarray_FxProperty__                                     toPXArray<FxProperty>
#define tolua_toxarray_XEAnimComponentPlayList__AnimWrapper             toXArray<XEAnimComponentPlayList::AnimWrapper>
#define tolua_toxarray_xes__Face__                                      toPXArray<xes::Face>
#define tolua_toxarray_AR__XEARAnchor__                                 toPXArray<AR::XEARAnchor>
#define tolua_toxarray_XEActor__                                        toPXArray<XEActor>
#define tolua_toxarray_IXEUserNodeFactory__                             toPXArray<IXEUserNodeFactory>
#define tolua_toxarray_IXBrushPrimitive__XBrushShape                    toXArray<IXBrushPrimitive::XBrushShape>
#define tolua_toxarray_XEHitResult                                      toXArray<XEHitResult>
#define tolua_toxarray_Scene__                                          toPXArray<Scene>
#define tolua_toxarray_XUIFiniteTimeAction__                            toPXArray<XUIFiniteTimeAction>
#define tolua_toxarray_XUINode__                                        toPXArray<XUINode>
#define tolua_toxarray_IXCloth__                                        toPXArray<IXCloth>
#define tolua_toxarray_XBlendShapeTarget                                toXArray<XBlendShapeTarget>
#define tolua_toxarray_XBlendShapeChannel__TargetPair                   toXArray<XBlendShapeChannel::TargetPair>
#define tolua_toxarray_XBlendShapeChannel                               toXArray<XBlendShapeChannel>
#define tolua_toxarray_IXSkeletalPhysicsRes__XPhyConstraintBoneNames    toXArray<IXSkeletalPhysicsRes::XPhyConstraintBoneNames>
#define tolua_toxarray_xes__Hand__Joint                                 toXArray<xes::Hand::Joint>
#define tolua_toxarray_xes__Hand__Gesture                               toXArray<xes::Hand::Gesture>
#define tolua_toxarray_xes__Hand__                                      toXArray<xes::Hand*>
#define tolua_toxarray_XEAnimMonBase__                                  toPXArray<XEAnimMonBase*>
#define tolua_toxarray_XEAnimMonElement__MetaData                       toXArray<XEAnimMonElement::MetaData>
#define tolua_toxarray_XUIGuidePage__                                   toPXArray<XUIGuidePage>
#define tolua_toxarray_XUINode__                                        toPXArray<XUINode>
#define tolua_toxarray_XBlendShapeInstance__SkinBlendShapePack__BlendShapeVertexDefinePack\
                                                                        toXArray<XBlendShapeInstance::SkinBlendShapePack::BlendShapeVertexDefinePack>
#define tolua_pushxarray_XBlendShapeInstance__SkinBlendShapePack__BlendShapeVertexDefinePack(L, arr)\
                                                                        pushXArray(L,arr,"XBlendShapeInstance::SkinBlendShapePack::BlendShapeVertexDefinePack")


#endif //XES_tolua_FIX_H
